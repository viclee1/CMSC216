/* 117213218 */
#include <sys/wait.h>
#include <sysexits.h>
#include <stdlib.h>
#include <err.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include "command.h"
#include "executor.h"
#define MAX_LINE 1024
#define PERMISSIONS 0664
static void print_tree(struct tree *t);
int aux_execute(struct tree *t, int parent_input_fd, int parent_output_fd);

int execute(struct tree *t) {
	if (t != NULL) {
		return aux_execute(t, -1, -1);
	}
   	return 0;
}

int aux_execute(struct tree *t, int parent_input_fd, int parent_output_fd) {
	pid_t fd;
	int status;
	if (t->conjunction == NONE) {
		if (strcmp("exit", t->argv[0]) == 0) {
			exit(0);
		} else if (strcmp("cd", t->argv[0]) == 0) {
			if (t->argv[1] == NULL) {
				getenv("HOME");
			} else if (chdir(t->argv[1]) != 0) {
				fprintf(stderr, "%s", t->argv[1]);
			}
		} else {
			fd = fork();
			if (fd == -1) {
				err(EX_OSERR, "fork error");
			} else if (fd == 0) {
				if (t->input != NULL) {
					if ((parent_input_fd = open(t->input, O_RDONLY)) < 0) {
						err(EX_OSERR,"Cannot open file");
					}
					if (dup2(parent_input_fd, STDIN_FILENO)) {
						err(EX_OSERR, "dup2 error");
					}

					if (close(parent_input_fd)) {
						err(EX_OSERR, "Closing file failed");
					}
                        	}

                        	if (t->output != NULL) {
					if (parent_output_fd = open(t->output, 
								    O_WRONLY | O_CREAT 
								    | O_TRUNC, 
								    PERMISSIONS) < 0) {
						err(EX_OSERR,"Cannot open file");
					}

					if (dup2(parent_output_fd, STDOUT_FILENO) < 0) {
						err(EX_OSERR, "dup2 error");
					}

					if (close(parent_output_fd) < 0) {
						err(EX_OSERR, "Closing file failed");
					}
                        	}

				execvp(t->argv[0], t->argv);
                       		fprintf(stderr, "Failed to execute %s\n", t->argv[0]);
                        	exit(EX_OSERR);
			} else {
				wait(&status);
				return status;
			}
		}
	} else if (t->conjunction == AND) {
		int status;
		if (t->input != NULL) {
			if ((parent_input_fd = open(t->input, O_RDONLY)) < 0) {
				err(EX_OSERR,"Cannot open file");
			}
		}

		if (t->output != NULL) {
			if ((parent_output_fd = open(t->output, O_WRONLY | O_CREAT | O_TRUNC, PERMISSIONS)) < 0) {
				err(EX_OSERR,"Cannot open file");
			}
		}
		status = aux_execute(t->left, parent_input_fd, parent_output_fd);
		if (status == 0) {
			return aux_execute(t->right, parent_input_fd, parent_output_fd);
		} else {
			return status;
		}

	} else if (t->conjunction == PIPE) {
		int pipefd[2];

		if (t->left->output != NULL) {
			printf("Ambiguous output redirect.\n");
			return -1;
		}

		if(t->right->input != NULL) {
			printf("Ambiguous input redirect.\n");
			return -1;
		}

		if (t->input != NULL) {
                        if ((parent_input_fd = open(t->input, O_RDONLY)) < 0 ) {
				err(EX_OSERR,"Cannot open file");
			}
                }
		
		if (t->output != NULL) {
			parent_output_fd = open(t->output, O_WRONLY | O_CREAT | O_TRUNC, PERMISSIONS);
		}

		if (pipe(pipefd) < 0) {
			err(EX_OSERR, "pipe error");
		}
		fd = fork();
		if (fd == -1) {
			err(EX_OSERR, "fork error");
		} else if (fd == 0) {
			close(pipefd[0]);
			if (dup2(pipefd[1], STDOUT_FILENO) < 0) {
				err(EX_OSERR, "dup2 error");
			}
			aux_execute(t->left, parent_input_fd, pipefd[1]);
			if (close(pipefd[1]) < 0) {
				err(EX_OSERR, "Closing file failed");
			}
		} else {
			close(pipefd[1]);
			if (dup2(pipefd[0], STDIN_FILENO) < 0) {
				err(EX_OSERR, "dup2 error");
			}
			aux_execute(t->right, parent_output_fd, pipefd[0]);
			if (close(pipefd[0]) < 0) {
				err(EX_OSERR, "Closing file failed");
			}
			wait(NULL);
		}

	} else if (t->conjunction == SUBSHELL) {
		if (t->input != NULL) {
			if ((parent_input_fd = open(t->input, O_RDONLY)) < 0) {
				err(EX_OSERR,"Cannot open file");
			}
		}
		
		if (t->output != NULL) {
			if ((parent_output_fd = open(t->output, O_WRONLY | O_CREAT 
                                		| O_TRUNC, PERMISSIONS)) < 0) {
				err(EX_OSERR, "Cannot open file");
			}
		}
		
		fd = fork();
		if (fd == 0) {
			aux_execute(t->left, parent_input_fd, parent_output_fd);
			exit(0);
		} else {
			wait(NULL);
		}
	}
	return 0;
}

static void print_tree(struct tree *t) {
	if (t != NULL) {
        	print_tree(t->left);

      		if (t->conjunction == NONE) {
         		printf("NONE: %s, ", t->argv[0]);
      		} else {
         		printf("%s, ", conj[t->conjunction]);
      		}
      		printf("IR: %s, ", t->input);
      		printf("OR: %s\n", t->output);

      		print_tree(t->right);
   	}
}
