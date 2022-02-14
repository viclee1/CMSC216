#include <stdio.h>
#include <string.h>
#include <sysexits.h>
#include <stdlib.h>
#include <ctype.h>
#include "document.h"
#define MAX_LEN 1024
/* Victor Lee, 117213218, vlee842 */

/* this function checks for the first argument provided to it */
int arg_check(const char *lines, char *arg){
	int i, cnt = 0, len, marker1 = -1, marker2 = -1;
	len = strlen(lines);
	for (i = 0; i < len; i++) {
		if (!(isspace(lines[i]))) {
			marker1 = i;
			break;
		}
	}
	for (i = i; i < len; i++) {
		if(isspace(lines[i])) {
			marker2 = i;
			break;
		}
	}
	
	for (i = marker1; i < marker2; i++ ) {
		arg[cnt++] = lines[i];
	}
	arg[cnt] = '\0';
	
	return 0;
}
	

int main(int argc, char *argv[]) {
	int i, num_param1 = 0, num_param2 = 0, cnt, len;
	FILE *input;
	char lines[MAX_LEN + 1],  text_param1[MAX_LEN + 1],
		command[MAX_LEN + 1], first_arg[MAX_LEN + 1] = {0};
	char *sub;
	const char *doc_name = "main_document";
	Document doc;

	if (argc > 2) {
		printf("Usage: user_interface\nUsage: user_interface <filename>\n");
		return EX_USAGE;	
	} else if (argc == 1) {
		input = stdin;
	} else {
		input = fopen(argv[1], "r");
		if (input == NULL) {
			fprintf(stderr, "%s cannot be opened.\n", argv[1]);
			return EX_OSERR;
		}
	}

	init_document(&doc, doc_name);

	fgets(lines, MAX_LEN + 1, input);
	while (!feof(input)) {
		if (argc == 1) {
			printf("> ");
		}
		
		/* ignores the comments with # */
		if(strstr(lines, "#") == NULL) {
			arg_check(lines, first_arg);
	                

			if (strcmp(first_arg, "add_paragraph_after") == 0) {
				if (sscanf(lines, " %s %d", command, &num_param1) == 2) {
					if(num_param1 >= 0) {
						if(add_paragraph_after(&doc, num_param1) == FAILURE){
							printf("add_paragraph_after failed\n");
						}
					} else {
						 printf("Invalid Command\n");
					}
				} else {
					printf("Invalid Command\n");
				}		
			} else if (strcmp(first_arg, "add_line_after") == 0) {
				if ((sub = strstr(lines, "*")) == NULL) {
					printf("Invalid Command\n");
				} else {
					char parse1[MAX_LEN + 1], parse2[MAX_LEN + 1];

					for(i = 0; lines[i] != '*'; i++) {
						parse1[i] = lines[i];
					}					
					strcpy(parse2, sub + 1);
					if((sscanf(parse1, " %s %d %d", command, 
						&num_param1, &num_param2) == 3) 
						&& num_param1 > 0 && num_param2 >= 0) {
						if(add_line_after(&doc, num_param1, 
							num_param2, parse2) == FAILURE) {
							printf("add_line_after failed");
						}
					} else {
						printf("Invalid Command\n");
					}
				}
			} else if (strcmp(first_arg, "print_document") == 0) {
				char tmp[MAX_LEN + 1];
				int comp;
				comp = sscanf(lines, " %s %s", command, tmp);
				if(comp == 1) {
					print_document(&doc);
				} else {
					printf("Invalid Command\n");
				}
			} else if (strcmp(first_arg, "append_line") == 0) {
				if ((sub = strstr(lines, "*")) == NULL) {
                                        printf("Invalid Command\n");
                                } else {
                                        char parse1[MAX_LEN + 1], parse2[MAX_LEN + 1];

                                        for(i = 0; lines[i] != '*'; i++) {
                                                parse1[i] = lines[i];
                                        }
                                        strcpy(parse2, sub + 1);

					if((sscanf(parse1, " %s %d", command, &num_param1) == 2)
						&& num_param1 > 0) {
						if (append_line(&doc, num_param1, parse2)
							== FAILURE) {
							printf("append_line failed");
						}
					} else {
						printf("Invalid Command");
					}
				}
			} else if (strcmp(first_arg, "remove_line") == 0) {
				if (sscanf(lines, " %s %d %d ", command, &num_param1, &num_param2) == 3) {
					if(num_param1 > 0 && num_param2 > 0) {
						if(remove_line(&doc, num_param1, 
							num_param2) == FAILURE){
							printf("remove_line failed\n");
						}
					} else {
						printf("Invalid Command\n");
					}
				} else {
					printf("Invalid Command\n");
				}
			} else if ((strcmp(first_arg, "load_file")) == 0) {
				if(sscanf(lines, " %s %s", command, text_param1) == 2) {
					if(load_file(&doc, text_param1) == FAILURE) {
						printf("load_file failed\n");
					}
				} else {
					printf("Invalid Command\n");
				}
			} else if (strcmp(first_arg, "replace_text") == 0) {
				char target[MAX_LEN + 1] = {0}, replacement[MAX_LEN + 1] = {0};
				len = strlen(lines);
				
				cnt = 0;
				for(i = 0; i < len; i++) {
					if(lines[i] == '"') {
						cnt++;
					}
				}
				/* checks if both arguments are in */
				if(cnt == 4) {
					cnt = 0;
					sub = strstr(lines, "\"");
					
					for (i = len - strlen(sub) + 1; lines[i] != '"'; i++) {
						target[cnt++] = lines[i];
					}
					/* calling this twice finds the 3rd instance of ", where replacement starts */
					sub = strstr(sub + 1, "\"");
					sub = strstr(sub + 1, "\"");
					cnt = 0;
					for(i = len - strlen(sub) + 1; lines[i] != '"'; i++) {
						replacement[cnt++] = lines[i];
					}

					if (replace_text(&doc, target, replacement) 
						== FAILURE) {
						printf("replace_text failed\n");
					}
				} else {
					/* checks if target and replacement exist */
					printf("Invalid Command\n");
				}
			} else if (strcmp(first_arg, "highlight_text") == 0) {
				char target[MAX_LEN + 1];
                                len = strlen(lines);
                                cnt = 0;
                                for(i = 0; i < len; i++) {
                                        if(lines[i] == '"') {
                                                cnt++;
                                        }
                                }
				/* checks if theres one argument is existant */
                                if(cnt == 2) {
                                        cnt = 0;
                                        sub = strstr(lines, "\"");
                                        for (i = len - strlen(sub) + 1; lines[i] != '"'; i++) {
                                                target[cnt++] = lines[i];
                                        }

                                        if(highlight_text(&doc, target) 
						== FAILURE) {
						printf("highlight_text failed\n");
					}

                                } else {
                                        printf("Invalid Command\n");
                                }
			} else if (strcmp(first_arg, "remove_text") == 0) {
				char target[MAX_LEN + 1];
                                len = strlen(lines);
                                cnt = 0;
                                for(i = 0; i < len; i++) {
                                        if(lines[i] == '"') {
                                                cnt++;
                                        }
                                }
                                /* checks if theres one argument is existant */
                                if(cnt == 2) {
                                        cnt = 0;
                                        sub = strstr(lines, "\"");
                                        for (i = len - strlen(sub) + 1; lines[i] != '"'; i++) {
                                                target[cnt++] = lines[i];
                                        }

                                        remove_text(&doc, target);
                                } else {
                                        printf("Invalid Command\n");
                                }
			} else if (strcmp(first_arg, "save_document") == 0) {
				if (sscanf(lines, " %s %s", command, text_param1) == 2) {
                                        if (save_document(&doc, text_param1) == FAILURE) {
                                                printf("save_document failed\n");
                                        }
                                } else {
                                        printf("Invalid Command\n");
				}
			} else if (strcmp(first_arg, "reset_document") == 0) {
				if (sscanf(lines, " %s", command) == 1) {
					reset_document(&doc);
				} else {
					printf("Invalid Command\n");
				}
			} else if (strcmp(first_arg, "quit") == 0 || 
				strcmp(first_arg, "exit") == 0) {
				if (sscanf(lines, " %s", command) == 1) {
					return EXIT_SUCCESS;
				} else {
					printf("Invalid Command\n");
				}
			} else if (*lines == '\n' || strspn(lines, " ") == 
					strlen(lines) - 1 || strcmp(lines, "") == 0) {
				/* ignore empty line */
			} else {
				printf("Invalid Command\n");
			}
		}

		fgets(lines, MAX_LEN + 1, input);
	}
	
	fclose(input);
	return EXIT_SUCCESS;
}
