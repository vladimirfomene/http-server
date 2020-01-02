#ifndef _HASHTABLE_H
#define _HASHTABLE_H

struct nlist {
	struct nlist *next;
	struct entry *entry_ptr;
};

int hashtable_size();
void init_hashtable();
struct entry *get_entry_ptr(char *pathname);
struct entry *remove_item(char *pathname);
struct entry *put_entry(struct entry *file_entry);

#endif
