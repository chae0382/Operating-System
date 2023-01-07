#include "myshell.h"

char *arg[MAX];
int argv;
bool full;
int p;
char *command_list[10];
char command[256];
int status, pid, d_pid;
int isBackground;

void tokenize(char *command){
	char *ptr = strtok(command, " \t\n");
	while (ptr != NULL){
		arg[argv++] = ptr;
		ptr = strtok(NULL, " \t\n");
	}
	arg[argv] = (char*)0;
	return;
}

int parse_background(){
	int end;
	for(int i = 0; i <256 ; i++){
		if(command[i] == '\n'){
			end = i;
			break;
		}	
	}
	if(command[end-1] == '&'){
		command[end-1] = ' ';
		return 1;
	}
	else{
		return 0;
	}
}

void cmd_quit(){
	printf("myshell developed by ChaeYeonLee(12191656).\n");
	exit(1);
}

void cmd_history(){
	if(full==false){
		for(int i = 0; i <p-1;i++){
			printf("%d	%s", i+1, command_list[i]);
		}
		printf("%d	%s", p, command_list[p-1]);
	}
	else{
		for(int i = 0; i <9; i++){
			printf("%d	%s", i+1, command_list[p]);
			p = (p+1)%10;
		}
		printf("10	%s", command_list[p]);
	}
}

void cmd_help(){
	printf("DESCRIPTION\nMyshell is a simple shell.\nThe following are built-in commands.\nquit : Shut down the shell program.\"myshell developed by ChaeYeonLee(12191656)\" is displayed at the end.\nhistory : It outputs up to 10 command lines that were recently entered by the user.\nhelp : Print out a simple manual.\n");
}

int main(){

	for(int i = 0; i < 10; i++){
		command_list[i] = malloc(256);
	}

	while(1){
	
		printf("12191656_shell$ ");
		argv = 0;
		fgets(command,256,stdin);
		
		strcpy(command_list[p], command);
		if(p==9){full = true;}
		p = (p+1)%10;

		isBackground = parse_background();
		tokenize(command);

		if(strcmp(arg[0], "quit")==0){
			cmd_quit();
		}	
		else if(strcmp(arg[0], "history")==0){
			cmd_history();
			continue;
		}
		else if(strcmp(arg[0], "help")==0){
			cmd_help();
			continue;
		}
		else{
			if((pid=fork())== -1){
				perror("fork failed");
			}
			else if (pid != 0){
				printf("[Parent]pid = %d\n", pid);
				if(isBackground==1){
					waitpid(pid, &status, WNOHANG);
				}
				else{
					wait(&status);
				}
				printf("[%d] : done!\n", pid);
			}
			else{
				execvp(arg[0], arg);
			}	
		}
	}

	for(int i = 0; i < 10; i++){
		free(command_list[i]);
	}
}	

