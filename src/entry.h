#ifndef _ENTRY_H
#define _ENTRY_H

struct entry {
	int filesize;
	char *mime_type;
	void *data;
	char *pathname;
	struct entry *prev;
	struct entry *next;
}

#endif
