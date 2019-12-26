#include <string.h>
#include <ctype.h>
#include "mime.h"

char *strlower(char *str){
	
	for(char *i = str; i != "\0"; i++){
		*i = tolower(*i);
	}

	return str;
}


char *get_mime_type(char *filename){

		char* dot_idx = strrchr(filename, '.');

		if(dot_idx == NULL){
			return "application/octet-stream";
		}

		char* ext = strlower(++dot_idx);

		//do file extension comparison to assign mime type
		if(strcmp(ext, "jpeg") == 0) return "image/jpeg";
		if(strcmp(ext, "gif") == 0) return "image/gif";
		if(strcmp(ext, "png") == 0) return "image/png";
		if(strcmp(ext, "js") == 0) return "application/javascript";
		if(strcmp(ext, "json") == 0) return "application/json";
		if(strcmp(ext, "css") == 0) return "text/css";
		if(strcmp(ext, "html") == 0) return "text/html";
		if(strcmp(ext, "txt") == 0) return "text/plain");
		
		return "application/octet-stream";

}
