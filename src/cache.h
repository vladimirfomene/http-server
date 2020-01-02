#ifndef _CACHE_H
#define _CACHE_H

struct entry *put_cache(char* filename);
struct entry *get_cache(char* filename);
void init_cache();

#endif
