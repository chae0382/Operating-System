#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdbool.h>
#define MAX 10

void tokenize(char*);
int parse_background();
void cmd_quit();
void cmd_history();
void cmd_help();

