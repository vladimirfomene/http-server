#ifndef _FILE_H
#define _FILE_H

struct file_data {
	char *filename;
	char *content;
	size_t size;
};


struct file_data *load_file(char *filename);
void print_file_entry(struct file_data *file_entry);
void free_file_data(struct file_data *data);

#endif
