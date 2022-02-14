/* Implement your shell here */
#include <sys/wait.h>
#include <sysexits.h>
#include <stdlib.h>
#include <err.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#define MAX_LEN 1024

int main() {
	pid_t fd;
	char *arg_list[3], lines[MAX_LEN + 1] = {0}, holder1[MAX_LEN + 1] = {0}, holder2[MAX_LEN + 1] = {0};
	
	FILE *file = stdin;
	printf("shell_jr: ");
	fflush(stdout);
	while (fgets(lines, MAX_LEN + 1, file) != NULL) {
        	sscanf(lines, " %s %s", holder1, holder2);	
		if (strcmp("exit", holder1) == 0 ||
                     strcmp("hastalavista", holder1) == 0) {
			printf("See you\n");
			exit(0);
		} else if (strcmp("cd", holder1) == 0) {
			if (chdir(holder2) != 0) {
				printf("Cannot change to directory %s\n", arg_list[1]);
			}
		} else {
			arg_list[0] = holder1;
			arg_list[1] = holder2;
			arg_list[2] = NULL;
			fd = fork();
			if (fd == -1) {
				perror("fork error");
			} else if (fd == 0) {
				execvp(holder1, arg_list);
				printf("Failed to execute %s\n", arg_list[0]);
				fflush(stdout);
				exit(EX_OSERR);
			} else {
				wait(NULL);
			}	
		}
		printf("shell_jr: ");
        	fflush(stdout);
	}
	return 0;
}
