#ifndef _NET_H
#define _NET_H

struct request_info {
	char *method;
	char *filepath;
	char *protocol;
};

int get_listener_socket(char *port);
void *get_in_addr(struct sockaddr *sa);

#endif
