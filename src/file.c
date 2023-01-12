#include <stdlib.h>
#include <stdio.h>

#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>

#include <sys/stat.h>
#include <sys/types.h>

//ADD ERROR CHECKING


//void gain_access();

//void return_access();

int file_exists(char* file_name){
	int fd = open(file_name, O_RDONLY);
	close(fd);
	return fd >= 0;
}

int file_size(char* file_name){
	struct stat st;
	stat(file_name, &st);
	return st.st_size;
}

char* file_content(char *file_name){
	int fd = open(file_name, O_RDONLY);
	int size = file_size(file_name);
	char* content = (char*)malloc(size);
	read(fd, content, size);
	close(fd);
	return content;
}

//should this replace??
int create_file(char* file_name, char* file_content){
	
}


void delete_file(char* file_name){
}

