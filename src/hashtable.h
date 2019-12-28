#ifndef _HASHTABLE_H
#define _HASHTABLE_H


struct nlist {
	struct nlist *next;
	struct entry *entry_ptr;
}

struct entry *get_entry_ptr(char *pathname);
struct enty *remove_entry(char *pathname);
struct entry *put_entry(struct entry *file_entry);

#endif
