#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

void error_check(int status, char* msg){
	if(status == -1){
		printf("%s: %s\n", msg, strerror(errno));
		exit(1);
	}

}
