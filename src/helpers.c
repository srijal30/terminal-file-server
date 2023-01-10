#include <stdlib.h>
#include <stdio.h>

#include <errno.h>
#include <string.h>

#define MAXLINE 100

void error_check(int status, char* msg){
	if(status == -1){
		printf("%s: %s\n", msg, strerror(errno));
		exit(1);
	}
	printf("%s: SUCCESS\n", msg);
}

char* get_input(char* msg){
	char* buf = (char*)malloc(MAXLINE);
	printf("%s", msg);
	fgets(buf, MAXLINE, stdin);
	buf[strlen(buf)-1] = 0;
	return buf;
}
