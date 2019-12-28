#ifndef _FILE_H
#define _FILE_H

struct file_data {
	char *filename;
	void* data;
	size_t size;
};


struct file_data *load_file(char *filename);
void free_file_data(struct file_data *data);

#endif
