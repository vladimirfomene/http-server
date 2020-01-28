#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include "entry.h"
#include "net.h"
#include "file.h"
#include "cache.h"
#include "dllist.h"
#include "hashtable.h"
#include "threadpool.h"

#define PORT "8080"
#define MAXDATASIZE 30000
#define NUM_THREADS 10

int read_from_client(char buf[], int sockfd);
struct request_info *get_request_info(char buf[]);
struct entry *request_handler(struct request_info *req);
char *response_builder(struct entry *req_entry, struct request_info *info);
void handle_connection(void *arg, pthread_mutex_t *lock);
char *get_local_time();

char buf[MAXDATASIZE];

int main(void){
	
	int sockfd, new_fd;
	struct sockaddr_storage their_addr;
	socklen_t sin_size;
	char ip6[INET6_ADDRSTRLEN];

	sockfd = get_listener_socket(PORT);
	printf("server: waiting for connections...\n");

	//create thread pool
	tpool_t *pool = tpool_create(NUM_THREADS);

	while(1) { // main accept() loop

		sin_size = sizeof their_addr;
		new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size);
		
		if (new_fd == -1) {
			perror("accept");
			continue;
		}

		inet_ntop(their_addr.ss_family,
		get_in_addr((struct sockaddr *) &their_addr),
		ip6, sizeof ip6);

		printf("server: got connection from %s\n", ip6);
		struct thread_arg args;
		args.lock = pool->work_mutex;
		args.param = &new_fd;
		tpool_add_work(pool, handle_connection, &args);

	}

	return 0;
}

int read_from_client(char buf[], int sockfd){
	int numbytes;
	if((numbytes = recv(sockfd, buf, MAXDATASIZE-1, 0)) == -1){
		perror("recv");
		return -1;
	}

	buf[numbytes] = '\0';
	return numbytes;
}

struct request_info *get_request_info(char buf[]){
	struct request_info *info = malloc(sizeof(struct request_info));
	char *method = strtok(buf, " ");
	char *filepath = strtok(NULL, " ");
	char *protocol = strtok(NULL, " ");
	
	info->method = method;
	info->filepath = filepath;
	info->protocol = protocol;

	return info;
}

struct entry *request_handler(struct request_info *req){
	strcat("files", req->filepath);
	struct entry *cache_entry;
	if(strcmp(req->method, "GET") == 0){
		cache_entry = get_cache(req->filepath);
	}
	
	return cache_entry;
}

char *response_builder(struct entry *req_entry, struct request_info *info){
	char *status_code;
	char *status_text;
	char *response_text;

	if(req_entry == NULL){
		status_code = "404";
		status_text = "NOT FOUND";
	}else {
		status_code = "200";
		status_text = "OK";
	}

	char* protocol_line = "";
	strcat(protocol_line, info->protocol);
	strcat(protocol_line, "");
	strcat(protocol_line, status_code);
	strcat(protocol_line, "");
	strcat(protocol_line, status_text);
	strcat(protocol_line, "\n");
	strcat(response_text, protocol_line);
	char *date_line = strcat("Date: ", get_local_time());
	strcat(date_line, "\n");
	strcat(response_text, date_line);
	char *connection_line = "Connection: close\n";
	strcat(response_text, connection_line);
	char *content_len_line = strcat("Content-Length: ", (char *) req_entry->filesize);
	strcat(content_len_line, "\n");
	strcat(response_text, content_len_line);
	char *content_type_line = strcat("Content-Type: ", req_entry->mime_type);
	strcat(content_type_line, "\n\n");
	strcat(response_text, content_type_line);
	strcat(response_text, req_entry->data);
	
	return response_text;
	
}

void handle_connection(void *arg, pthread_mutex_t *lock){

	int *sock_fd = (int *) arg;
	read_from_client(buf, *sock_fd);
	struct request_info *request = get_request_info(buf);

	pthread_mutex_lock(lock);
	struct entry *req_entry = request_handler(request);
	pthread_mutex_unlock(lock);

	char *res = response_builder(req_entry, request);
	
	if (send(*sock_fd, res, req_entry->filesize, 0) == -1)
				perror("send");

	close(*sock_fd);
}

char *get_local_time(){
	struct tm* local; 
  time_t t = time(NULL); 
  
  // Get the localtime 
  local = localtime(&t); 
  return asctime(local); 

}
