#include <string.h>
#include <ctype.h>


char *strlower(char *str){
	
	for(char *i = str; i != "\0"; i++){
		*i = tolower(*i);
	}

	return str;
}


char *get_mime_type(char *filename){





}
