#include <stdlib.h>
#include "entry.h"
#include "file.h"

struct entry *head = NULL;
struct entry *tail = NULL;

void create_list(){
	head = malloc(sizeof(struct entry));
	tail = head;
}

void *add_list(struct entry *new_entry){
	struct entry *tmp = head;
	new_entry->next = tmp;
	head = new_entry;
	return new_entry;
}

void *remove_entry(struct entry *file_entry){
	struct entry *prev = file_entry->prev;
	prev->next = file_entry->next;
	return file_entry;
}

void free_dllist(){
	if(head == NULL)
		return;
	else {
		struct entry *tmp;
		while(head->next != NULL){
			 tmp = head->next;
			free(head);
			head = tmp;
		}
		free(head);
	}
}
