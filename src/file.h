#ifndef FILE_H
#define FILE_H

typedef struct fileitem {
	char name[256];
	int size;
	int type;
	//char* content; //stores the content of item
} FILEITEM;

FILEITEM** get_items(char* path);

void free_items(FILEITEM** items);

int create_semaphore(int val, int perms);

void remove_semaphore();

int get_semaphore();

void gain_access();

void return_access();

//returns TRUE(1) or FALSE(0)
int file_exists(char* file_name);

int file_size(char* file_name);

char* file_content(char *file_name);

void create_file(char* file_name, char* file_content);

void delete_file(char* file_name);

#endif
