#ifndef _NET_H
#define _NET_H

int get_listener_socket(char *port);
void *get_in_addr(struct sockaddr *sa);

#endif
