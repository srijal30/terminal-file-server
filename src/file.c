#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <unistd.h>
#include <fcntl.h>

#include <dirent.h>
#include <sys/stat.h>

#include <sys/sem.h>
#include <sys/ipc.h>

#include "helpers.h"
#include "file.h"


//TAKEN FROM LAB 14 AND MODIFIED
int KEY = 100792036;

union semun {
  int val;
  struct semid_ds *buf;
  unsigned short  *array;
  struct seminfo  *__buf;
};

int create_semaphore(int val, int perms){
	//create the semaphore (always override)
	int semid = semget(KEY, 1, IPC_CREAT | perms);
	error_check(semid, "CREATE SEMAPHORE");
	//set the value of semaphore
	union semun us;
	us.val = val;
	error_check(semctl(semid, 0, SETVAL, us), "CREATE SEMAPHORE");
	return semid;
}

int get_semaphore(){
	int semid = semget(KEY, 1, 0);
	error_check(semid, "GET SEMAPHORE");
	return semid;
}

void remove_semaphore(){
	int semid = get_semaphore();
	error_check(semctl(semid, -69, IPC_RMID), "REMOVE SEMAPHORE");
}

void gain_access(){
	int semid = get_semaphore();
	struct sembuf sem;
	sem.sem_num = 0;
	sem.sem_op = -1; //decrement
	sem.sem_flg = IPC_NOWAIT;
	int success = semop(semid, &sem, 1);
	while(success == -1) success = semop(semid, &sem, 1);
}

void return_access(){
	int semid = get_semaphore();
	struct sembuf sem;
	sem.sem_num = 0;
	sem.sem_op = 1; //decrement
	sem.sem_flg = IPC_NOWAIT;
	error_check(semop(semid, &sem, 1), "RETURNING ACESS");
}

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

char* directory_content(char* dir_name){
	char* content = (char*)calloc(25600, 1); 
	//run the command
	char buf[256] = "ls ";
	strcat(buf, dir_name);
	FILE* ls = popen(buf, "r");
	//create content
	while(fgets(buf, 256, ls) != NULL){
		strcat(content, buf);
	}
	pclose(ls);
	return content;
}

void create_file(char* file_name, char* file_content){
	int fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	error_check(write(fd, file_content, strlen(file_content)), "CREATE FILE");
	close(fd);
}

void delete_file(char* file_name){
	error_check(remove(file_name), "REMOVE FILE");
}

FILEITEM* get_item(struct dirent* entry){
	FILEITEM* newItem = (FILEITEM*)malloc(sizeof(FILEITEM));
	//get the size
	struct stat st;
	error_check(stat(entry->d_name, &st), "GETTING ITEM'S stat");
	newItem->size = st.st_size;
	//get the name & type
	newItem->type = entry->d_type;
	printf("\nCOPYING \"%s\" TO \"%s\"\n", entry->d_name, newItem->name);//DEBUG
	strncpy(newItem->name, entry->d_name, 255);
	(newItem->name)[255] = 0;
	//get the content
	//for file
	if(newItem->type == 8) newItem->content = file_content(entry->d_name);
	//for directory	
	else if(newItem->type == 4) newItem->content = directory_content(entry->d_name);
	//make the size the size of content
	newItem->size = strlen(newItem->content);
	return newItem;
}

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

void free_items(FILEITEM** items){
	int cnt = 0;
	do{
		free(items[cnt]->content);
		free(items[cnt++]);
	}
	while(items[cnt] != NULL);
	free(items);
}

