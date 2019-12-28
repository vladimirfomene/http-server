#ifndef _DLLIST_H
#define _DLLIST_H

void create_list();
void *add_list(struct entry *head);
void *remove_entry(struct entry *file_entry);
void free_dllist(struct entry *file_entry);

#endif
