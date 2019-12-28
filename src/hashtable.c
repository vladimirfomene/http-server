#include "hashtable.h"

#define HASHSIZE 101

static struct nlist *hashtab[HASHSIZE];
static int num_entry = 0;

unsigned hash(char *s){
	unsigned hashval;

	for(hashval = 0; *s != '\0'; s++)
		hashval = *s + 31 * hashval;
	return hashval % HASHSIZE;

}


struct entry *get_entry_ptr(char *s){

	struct nlist *np;

	for(np = hashtab[hash(s)]; np != NULL; np = np->next)
		if(strcmp(s, np->pathname) == 0)
			return np->entry_ptr;

	return NULL;

}

struct entry *put_entry(struct entry *entry_ptr){

	struct nlist *np;
	unsigned hashval;

	if((np = lookup(entry_ptr->pathname)) == NULL) {
		np = (struct nlist *) malloc(sizeof(*np));
	
		hashval = hash(entry_ptr->pathname);
		np->next = hashtab[hashval];
		hashtab[hashval] = np;
		num_entry++;
	}

	np->entry_ptr = entry_ptr;
	return np->entry_ptr;

}

struct entry *remove_entry(char *pathname){

	struct nlist *np;

	for(np = hashtab[hash(pathname)]; np != NULL; np = np->next)
		if(strcmp(pathname, np->pathname) == 0){
				struct entry *tmp = np->next;
				if(*tmp == NULL){
					np = NULL
				}
			
				np->next = tmp->next;
				np->entry_ptr = tmp->entry_ptr;
		
				return np->entry_ptr;
				
		}
			

	return NULL;

}
