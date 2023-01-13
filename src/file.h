#ifndef FILE_H
#define FILE_H

typedef struct file {
	char name[50];	
	struct stat st;
} ITEM;


void gain_access();

void return_access();

//0 for no 1 for yes
int file_exists(char* file_name);

int file_size(char* file_name);

char* file_content(char *file_name);

void create_file(char* file_name, char* file_content);

void delete_file(char* file_name);

#endif
