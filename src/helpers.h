#ifndef HELPERS_H
#define HELPERS_H

//toggles between printing out debug print statements
void debug(int mode);

//if status is -1, program exits after printing errno and msg
void error_check(int status, char* msg);

//gets input from stdin
char* get_input(char* msg);

#endif
