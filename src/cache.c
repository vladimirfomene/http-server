#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include "entry.h"
#include "cache.h"
#include "dllist.h"
#include "hashtable.h"
#include "file.h"
#include "mime.h"


#define MAX_CACHE_SIZE 5


void init_cache(){
	//Initialize dllist
	create_list();
	init_hashtable();
}


struct entry *put_cache(char* filename){

	struct file_data *file_data = load_file(filename);
	struct entry *file_entry = malloc(sizeof(struct entry));
	file_entry->filesize = file_data->size;
	file_entry->mime_type = get_mime_type(file_data->filename);
	file_entry->data = file_data->content;
	file_entry->pathname = file_data->filename;
	file_entry->prev = NULL;
	file_entry->next = NULL;
	if(dllist_size() == MAX_CACHE_SIZE){
		//remove least recently used entry
		remove_tail();
		struct entry *removed_entry;
		if((removed_entry = remove_item(file_entry->pathname)) == NULL){
			printf("Remove from hashtable failed");
		}
	}
	
	struct entry *new_entry = add_entry(file_entry);
	struct entry *entry_ptr = put_entry(new_entry);

	return entry_ptr;
	
}


struct entry *get_cache(char *filename){
	struct entry *entry_ptr = get_entry_ptr(filename);
	
	if(entry_ptr == NULL){
		//read from disk and add to cache
		return put_cache(filename);
	}
	
	struct entry *cache_entry = remove_entry(entry_ptr);
	return add_entry(cache_entry);
}
