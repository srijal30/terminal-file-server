#ifndef FILE_H
#define FILE_H

//stores info for a fileitem (file or directory)
typedef struct fileitem {
	char name[256];
	int size;
	int type;
	char* content;
} FILEITEM;

//returns a list of fileitems in specified path
FILEITEM** get_items(char* path);

//frees list of filetiems
void free_items(FILEITEM** items);

//creates a semaphore and returns semid
int create_semaphore(int val, int perms);

//remove sempahore associated with program's key
void remove_semaphore();

//gets semaphore id associeted with program's key
int get_semaphore();

//waits until semaphore is available
void gain_access();

//returns access so other processes can access semaphore
void return_access();

//returns TRUE(1) or FALSE(0) depending on if file exists
int file_exists(char* file_name);

//returns size of specified file
int file_size(char* file_name);

//returns string of content of specified file
char* file_content(char *file_name);

//creates a file based on filename and content given
void create_file(char* file_name, char* file_content);

//deletes file with filename if it exists
void delete_file(char* file_name);

//runs "ls" and returns string wih the output
char* directory_content(char* dir_name);

#endif
