#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include "entry.h"
#include "dllist.h"

struct entry *head = NULL;
struct entry *tail = NULL;
static int list_size = 0;

void create_list(){
	head = malloc(sizeof(struct entry));
	tail = head;
}

void *add_entry(struct entry *new_entry){
	struct entry *tmp = head;
	new_entry->next = tmp;
	head = new_entry;
	list_size++;
	return head;
}

struct entry *remove_entry(struct entry *file_entry){
	struct entry *prev = file_entry->prev;
	prev->next = file_entry->next;
	list_size--;
	return file_entry;
}

void remove_tail(){
	tail = tail->prev;
	tail->next = NULL;
	list_size--;
}

void print_list(){
	struct entry *curr;
	for(curr = head; curr != NULL; curr = curr->next){
		printf("pathname: %s\n", curr->pathname);
	}
}

int dllist_size(){
	return list_size;
}

void free_dllist(){
	if(head == NULL)
		return;
	else {
		struct entry *tmp;
		while(head->next != NULL){
			 tmp = head->next;
			free(head);
			list_size--;
			head = tmp;
		}
		free(head);
	}
}
