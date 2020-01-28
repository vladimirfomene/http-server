#ifndef _DLLIST_H
#define _DLLIST_H

void create_list();
void print_list();
int dllist_size();
void remove_tail();
void *add_entry(struct entry *new_entry);
struct entry *remove_entry(struct entry *file_entry);
void free_dllist();

#endif
