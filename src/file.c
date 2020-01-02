#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "file.h"


struct file_data *load_file(char *filename){

	
	struct stat file_info;

	//open file
	FILE *fp = fopen(filename, "rb");
	
	if(fp == NULL){
		return NULL;
	}

	if(stat(filename, &file_info) == -1){
		return NULL;
	}

	//create buffer
	char *buffer = (char *) malloc(file_info.st_size);
		
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
	file_entry->content = buffer;
	file_entry->size = file_info.st_size;

	//return buffer
	return file_entry;
}

void print_file_entry(struct file_data *file_entry){
	for(int i = 0; i < file_entry->size; i++){
		printf("%s", file_entry->content);
	}
}


void free_file_data(struct file_data *file_entry){
		free(file_entry->content);
		free(file_entry);
}
