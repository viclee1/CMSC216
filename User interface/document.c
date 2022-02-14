#include <stdio.h>
#include <string.h>
#include "document.h"
/* Victor Lee, 117213218, vlee842 */

/* initializes document structure if the given parameters are usable 
 * returns null if name is larger than MAX_STR_SIZE,  name is less than 1
 * or if doc or name are null, success otherwise */
int init_document(Document *doc, const char *name){
	
	if (doc == NULL || name == NULL ||strlen(name) > MAX_STR_SIZE ||strlen(name) < 1) {
		return FAILURE;
	} else {

		strcpy(doc->name, name);
		doc->number_of_paragraphs = 0;
		return SUCCESS;
	}
}

/* sets the number of paragraphs to 0 as long as doc is not null
 * returns failure if doc is null, success otherwise */
int reset_document(Document *doc){
	if (doc == NULL) {
		return FAILURE;
	} else {
		doc->number_of_paragraphs = 0;
		return SUCCESS;
	}
}

/* prints information about document and each paragraph and its lines in the document structure 
 * returns failure if doc is null, success otherwise */
int print_document(Document *doc){
	if(doc == NULL){
		return FAILURE;
	} else {
		int i, j;

		printf("Document name: \"%s\"\n", doc->name);
		printf("Number of Paragraphs: %d\n", doc->number_of_paragraphs);

		for(i = 0; i < doc->number_of_paragraphs; i++){
			for(j = 0; j < doc->paragraphs[i].number_of_lines; j++) {
				printf("%s", doc->paragraphs[i].lines[j]);
			}
			if(i < doc->number_of_paragraphs - 1 && doc->number_of_paragraphs > 1){
 	                	printf("\n"); 
	                }
		}
		return SUCCESS;
	}
}

/* Adds a paragraph after the specified paragraph number 
 * returns null if doc is null, paragraph_number is larger than max paragraphs or less than 0,
 * or if doc is already at max paragraphs, success otherwise*/
int add_paragraph_after(Document *doc, int paragraph_number){
	if(doc == NULL || doc->number_of_paragraphs >= MAX_PARAGRAPHS || paragraph_number < 0 
		|| paragraph_number > doc->number_of_paragraphs){
		return FAILURE;
	} else {
		int i, j;
		Paragraph new_para;
		new_para.number_of_lines = 0;
		/* moves paragraphs forward one space in the array to fit in the new paragraph number */
		if(doc->number_of_paragraphs > 0){
			for(i = doc->number_of_paragraphs; i > paragraph_number; i--){
				doc->paragraphs[i].number_of_lines = doc->paragraphs[i - 1].number_of_lines;
				for(j = 0; j < doc->paragraphs[i].number_of_lines; j++){
					strcpy(doc->paragraphs[i].lines[j], doc->paragraphs[i - 1].lines[j]);
				}
			}
		}
		doc->paragraphs[paragraph_number] = new_para;
		doc->number_of_paragraphs++;
		return SUCCESS;
	}
}

/* Adds a new line after the line with the specified line number 
 * Failure if doc or new_line are null, paragaph_number is larger than number of paragraphs, line_number is less than
 * 0, or if the paragraph is at max lines */
int add_line_after(Document *doc, int paragraph_number, int line_number, const char *new_line){
	int arr_loc = paragraph_number - 1, 
		num_lines = doc->paragraphs[arr_loc].number_of_lines;

	if(doc == NULL || paragraph_number > doc->number_of_paragraphs ||
		num_lines >= MAX_PARAGRAPH_LINES || line_number < 0 || 
		line_number > num_lines || new_line == NULL 
		|| paragraph_number <= 0){
		return FAILURE;
	} else {
		int i;
		
		if(line_number == 0 && num_lines == 0){
			strcpy(doc->paragraphs[arr_loc].lines[0],  new_line);
		} else {
			for(i = num_lines; i > line_number; i--){
              			strcpy(doc->paragraphs[arr_loc].lines[i],  doc->paragraphs[arr_loc].lines[i - 1]);
     			}
			if(line_number == 0){
				strcpy(doc->paragraphs[arr_loc].lines[0], new_line);
			} else {
			 	strcpy(doc->paragraphs[arr_loc].lines[line_number], new_line);
			}
			
		}
		doc->paragraphs[arr_loc].number_of_lines++;
		return SUCCESS;	
	}
}

/* Returns the number of lines in a paragraph using the number of lines out parameter 
 * Failure if doc or number_of_lines are null, paragraph_number is larger than
 * the number of paragraphs it has */
int get_number_lines_paragraph(Document *doc, int paragraph_number, int *number_of_lines){
	if(doc == NULL || paragraph_number > doc->number_of_paragraphs || number_of_lines == NULL){
		return FAILURE;
	} else {
		*number_of_lines = doc->paragraphs[paragraph_number].number_of_lines;	
		return SUCCESS;
	}
}

/* Appends a new line to the specified paragraph. 
 * Follow same Failure and Success as add_line_after */
int append_line(Document *doc, int paragraph_number, const char *new_line){
	int arr_loc = paragraph_number - 1, 
		num_lines = doc->paragraphs[arr_loc].number_of_lines;

        if(doc == NULL || paragraph_number > doc->number_of_paragraphs ||
                num_lines >= MAX_PARAGRAPH_LINES || new_line == NULL ||
		paragraph_number <= 0){
                return FAILURE;
        } else {
		/* simplifies add_lines_after to only adding new strings at the end of the non null part 
 * 	   	of the array*/
		strcpy(doc->paragraphs[arr_loc].lines[num_lines], new_line);
		doc->paragraphs[arr_loc].number_of_lines++;
		return SUCCESS;
	}
}

/* Removes the specified line from the paragraph. Returns null if document is null
 * , paragraph_number is larger than the number of paragraphs in document or if 
 * line number is larger than the paragraph_number's number of lines */
int remove_line(Document *doc, int paragraph_number, int line_number){
	int arr_loc = paragraph_number - 1;
	if(doc == NULL || paragraph_number > doc->number_of_paragraphs || 
		line_number > doc->paragraphs[arr_loc].number_of_lines){
			return FAILURE;
	} else {
		int i, num_lines = doc->paragraphs[arr_loc].number_of_lines;
		/* essentially writes over the line that needs to be removed */
		for(i = line_number - 1; i < num_lines; i++){
		strcpy(doc->paragraphs[arr_loc].lines[i],  doc->paragraphs[arr_loc].lines[i + 1]);
		}
		/* decrements number of lines also makes extra string at the end less accessible */
		doc->paragraphs[arr_loc].number_of_lines--;
		return SUCCESS;
	}
}

/* Adds the first data lines number of rows from the data array to the document, starting a new paragraph
 * at the beginning of the document. A row with an empty string starts a new paragraph 
 * Returns failure if the parameters are null or it manages to exceed max paragraphs or max lines in a paragraph
 * else return success*/
int load_document(Document *doc, char data[][MAX_STR_SIZE + 1], int data_lines){
	if(doc == NULL || data == NULL || data_lines == 0 || doc->number_of_paragraphs >= MAX_PARAGRAPHS){
		return FAILURE;
	} else {
		int i, cnt = 0;
        	add_paragraph_after(doc, cnt++);
       
		for(i = 0; i < data_lines; i++){
			if(strcmp(data[i], "") == 0) {
				if(add_paragraph_after(doc, cnt++) == FAILURE){
					return FAILURE;
				}
			} else {
				if(append_line(doc, cnt, data[i]) == FAILURE){
					return FAILURE;
				}
			}
		}
		return SUCCESS;
	}
}

/* Follows a similar operation to load_document, except it does so from a file instead.
 * Returns fail if doc or file is null, or if opening the file fails*/
int load_file(Document *doc, const char *filename){
	if (doc == NULL || filename == NULL) { 
        	return FAILURE; 
	} else { 
	        int cnt = 0, spc_cnt;
	        char file_contents[MAX_STR_SIZE + 1] = {0}; 
	        FILE *file = fopen(filename, "r"); 
	        if (file == NULL) { 
	        	return FAILURE; 
	        } else {
	        	add_paragraph_after(doc, cnt++);  
	                                  
	                while (fgets(file_contents, MAX_STR_SIZE + 1, file) != NULL) {  
				spc_cnt = strspn(file_contents, " ");
				
	                        if (spc_cnt == ((int)strlen(file_contents) - 1)
					|| file_contents[0] == '\n' ||
					file_contents[0] == '\0') {  
	                        	add_paragraph_after(doc, cnt++);
	                        } else {  
	                        	append_line(doc, cnt, file_contents); 
	                        } 
	                }  
	                fclose(file);  
	                return SUCCESS;  
	        }
	}
} 

/* This function prints the document to the specified file (overwriting the
 * file). The function returns FAILURE if doc is NULL, filename is NULL, or the
 * file cannot be opened. */
int save_document(Document *doc, const char *filename){
	if (doc == NULL || filename == NULL) {
		return FAILURE;
	} else {
		int i, j;
		FILE *file = fopen(filename, "w+");
		if(file == NULL){
			return FAILURE;
		}
	
		for(i = 0; i < doc->number_of_paragraphs; i++){
                	for(j = 0; j < doc->paragraphs[i].number_of_lines; j++){
				fputs(doc->paragraphs[i].lines[j], file);
				fputs("\n", file);
			}
			if(i < doc->number_of_paragraphs - 1 && doc->number_of_paragraphs > 1){
                                fputs("\n", file);
                        }
		}	

		fclose(file);
		return SUCCESS;
	}
}
/* Replaces every appearance of the text target in the document with the text replacement 
 * returns Failure if doc, target, or replacement are null, success otherwise */
int replace_text(Document *doc, const char *target, const char *replacement){ 
	if(doc == NULL || target == NULL || replacement == NULL){ 
		return FAILURE; 
	} else {
		int i, j, tlen = strlen(target), rlen = strlen(replacement);  
		char *p;  
		for(i = 0; i < doc->number_of_paragraphs; i++){  
	        	for(j = 0; j < doc->paragraphs[i].number_of_lines; j++){  
	                	p = strstr(doc->paragraphs[i].lines[j], target);  
	                	while(p != NULL){
	                        	memmove(p + rlen, p + tlen, strlen(p) - tlen + 1);  
	                        	memmove(p, replacement, rlen);
					p =  strstr(p + rlen, target);
	                	}
	        	}
	  	}
	  	return SUCCESS;
	}
} 

/* Highlights every appearance of the text target in the document 
 * returns Failure if doc, target, success otherwise*/
int highlight_text(Document *doc, const char *target){
	if(doc == NULL || target == NULL){
		return FAILURE;
	} else {
        	char highlight[MAX_STR_SIZE + 1] = {0};

		/* uses an emtpy string and concatenated to look 
 * 		like the target but "highlighted" */
		strcat(highlight, HIGHLIGHT_START_STR);
		strcat(highlight, target);
		strcat(highlight, HIGHLIGHT_END_STR);
		replace_text(doc, target, highlight);
		return SUCCESS;	
	}
}

/* Removes every appearance of the text target in the document 
 * returns Failure if doc, target, success otherwise */
int remove_text(Document *doc, const char *target){
	if(doc == NULL || target == NULL){
                return FAILURE;
        } else {
		int i, j, tlen = strlen(target);
        	char *p;
        	for(i = 0; i < doc->number_of_paragraphs; i++){
        		for(j = 0; j < doc->paragraphs[i].number_of_lines; j++){
                		p = strstr(doc->paragraphs[i].lines[j], target);
                		while(p != NULL){
				/* the if statement makes sure that the remove 
 * 				function does not remove parts of a word just 
 * 				because it matches */
				if((strcmp(doc->paragraphs[i].lines[j], p) == 0 
					|| *(p - 1) == ' ') && ((*(p + tlen) < 'A') 
					||(*(p + tlen) > 'Z' && *(p + tlen) < 'a') 
					|| (*(p + tlen) > 'z') || *(p + tlen) == ' ' 
					|| *(p + tlen) == '\0')) {
                        			memmove(p, p + tlen, 
						strlen(p) - tlen + 1);
					}
                              	p =  strstr(p + 1, target);
				}
                	}
		}
        	return SUCCESS;
	}
}
