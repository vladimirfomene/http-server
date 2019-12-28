#include <stdio.h>
#include <stdlib.h>
#include "file.h"

#define BUFF_SIZE 100

struct file_data *load_file(char *filename){
	
	struct stat file_info;

	//open file
	File *fp = fopen(filename, "rb");
	
	if(fp == NULL){
		return NULL;
	}

	if(stat(filename, &file_info) == 0){
		return NULL;
	}

	//create buffer
	char *buffer = malloc(file_info.st_size);
		
	//read from file into buffer
	int num_read = fread(buffer, sizeof(char), file_info.st_size, fp);

	if(num_read != file_info.st_size){
		return NULL;
	}

	
	//close file
	fclose(fp);

	//building file_data struct
	struct file_data *file_entry = malloc(sizeof(struct file_data));
	file_entry->filename = filename;
	file_entry->data = buffer;
	file_entry->size = file_info.st_size;

	//return buffer
	return file_entry;
}


void free_file_data(struct file_data *file_entry){
		free(file_entry->data);
		free(file_entry);
}
