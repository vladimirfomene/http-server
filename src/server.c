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
#include "net.h"

#define PORT "8080"


int main(void){
	
	int sockfd, new_fd;
	struct sockaddr_storage their_addr;
	socklen_t sin_size;
	char ip6[INET6_ADDRSTRLEN];

	sockfd = get_listener_socket(PORT);
	printf("server: waiting for connections...\n");

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

		if (send(new_fd, "Hello, world!", 13, 0) == -1)
				perror("send");

		close(new_fd);

	}

	return 0;
}










