#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>

#include <sys/stat.h>
#include <sys/types.h>

#include "helpers.h"

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

