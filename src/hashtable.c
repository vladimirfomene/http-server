#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>
#include "entry.h"
#include "hashtable.h"

#define HASHSIZE 101
static int table_size = 0;

static struct nlist *hashtab[HASHSIZE];

unsigned hash(char *s){
	unsigned hashval;

	for(hashval = 0; *s != '\0'; s++)
		hashval = *s + 31 * hashval;
	return hashval % HASHSIZE;

}

void init_hashtable(){
	for(int i = 0; i < HASHSIZE; i++){
		hashtab[i] = NULL;
	}
}


struct entry *get_entry_ptr(char *s){
	struct nlist *np;
	for(np = hashtab[hash(s)]; np != NULL; np = np->next){
		if(strcmp(s, np->entry_ptr->pathname) == 0)
			return np->entry_ptr;
	}
	return NULL;

}

struct entry *put_entry(struct entry *entry_ptr){

	struct nlist *np;
	struct entry *found_entry;
	unsigned hashval;

	if((found_entry = get_entry_ptr(entry_ptr->pathname)) == NULL) {
		np = (struct nlist *) malloc(sizeof(struct nlist));
	
		hashval = hash(entry_ptr->pathname);
		np->next = hashtab[hashval];
		np->entry_ptr = entry_ptr;
		hashtab[hashval] = np;
		table_size++;
	}

	return np->entry_ptr;

}

int hashtable_size(){
	return table_size;
}

struct entry *remove_item(char *pathname){

	struct nlist *np;

	for(np = hashtab[hash(pathname)]; np != NULL; np = np->next){
		if(strcmp(pathname, np->entry_ptr->pathname) == 0){

				struct nlist *tmp = np->next;
				if(tmp == NULL){
					struct entry *ptr = np->entry_ptr;
					np = NULL;
					return ptr;
				}
			
				np->next = tmp->next;
				np->entry_ptr = tmp->entry_ptr;

				table_size--;
		
				return np->entry_ptr;
				
		}
	}
	return NULL;

}
