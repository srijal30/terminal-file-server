#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>

#include <sys/stat.h>

#include "helpers.h"
#include "file.h"

//ERROR CHECKING SHOULDNT END PROGRAM RIGHT??

//void gain_access();

//void return_access();

int file_exists(char* file_name){
	int fd = open(file_name, O_RDONLY);
	close(fd);
	return fd >= 0;
}

int file_size(char* file_name){
	struct stat st;
	error_check(stat(file_name, &st), "FILE SIZE");
	return st.st_size;
}

char* file_content(char *file_name){
	int fd = open(file_name, O_RDONLY);
	error_check(fd, "FILE CONTENT Invalid File");
	int size = file_size(file_name);
	char* content = (char*)malloc(size);
	error_check(read(fd, content, size), "FILE CONTENT Read");
	close(fd);
	return content;
}

//should this replace??
void create_file(char* file_name, char* file_content){
	int fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	error_check(write(fd, file_content, strlen(file_content)), "CREATE FILE");
	close(fd);
}

void delete_file(char* file_name){
	error_check(remove(file_name), "REMOVE FILE");
}

//DOES NOT WORK FOR DIFFERENT DIRECTORIES (we can use chdir)
//CREATE FILEITEM STRUCT
FILEITEM* get_item(struct dirent* entry){
	FILEITEM* newItem = (FILEITEM*)malloc(sizeof(FILEITEM));
	//get the size
	struct stat st;
	error_check(stat(entry->d_name, &st), "GETTING ITEM'S stat");
	newItem->size = st.st_size;
	//get the name & type
	newItem->type = entry->d_type;
	strncpy(newItem->name, entry->d_name, 256);
	return newItem;
}

//GETS LIST OF FILE ITEMS IN PATH
FILEITEM** get_items(char* path){
	FILEITEM** items = (FILEITEM**)malloc(sizeof(FILEITEM*));
	items[0] = NULL;
	int cnt = 0;
	//go through all the items in the dir path
	DIR* dir = opendir(path);
	struct dirent* entry = readdir(dir);
	while(entry != NULL){
		//dont add .
		if(strcmp(entry->d_name, ".") != 0){
			items[cnt] = get_item(entry);
			items = (FILEITEM**)realloc(items, 8*(++cnt+1));
			items[cnt] = NULL;
		}
		entry = readdir(dir);
	}
	closedir(dir);
	return items;
}

//FREES FILEITEM LIST
void free_items(FILEITEM** items){
	int cnt = 0;
	do{free(items[cnt++]);}
	while(items[cnt] != NULL);
	free(items);
}

