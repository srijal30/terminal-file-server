#ifndef FILE_H
#define FILE_H

#include <sys/stat.h>

typedef struct fileitem {
	char name[256];
	int size;
	int type; //d_type
	//char* content; //stores the content of item
} FILEITEM;

FILEITEM** get_items(char* path);

void free_items(FILEITEM** items);

void gain_access();

void return_access();

//0 for no 1 for yes
int file_exists(char* file_name);

int file_size(char* file_name);

char* file_content(char *file_name);

void create_file(char* file_name, char* file_content);

void delete_file(char* file_name);

#endif
