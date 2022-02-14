#include <stdio.h>
#include <string.h>
#include "text_manipulation.h"

int remove_spaces(const char *source, char *result, int *num_spaces_removed) {  
	
	int i, cnt = 0, spaces_to_remove = 0, marker = 0;
	int len = strlen(source);

	if(source == NULL || len == 0){
		return FAILURE;
	} else {

		for(i = 0; source[i] == ' '; i++){
			spaces_to_remove++;
		}
		
		if(*source == 0){
			result = 0;
			return SUCCESS;
		} 
			
		for(i = spaces_to_remove; i < len; i++){
			if((source[i] == ' ' && source[i + 1] == ' ') || 
				(source[i] == ' ' && source[i + 1] == '\0')){
				marker = i;
				break;
			}
			result[cnt] = source[i];
			cnt++;
		}
		
		result[cnt] = '\0';

		for(i = marker; i < len; i++){
			spaces_to_remove++;
		}
	
		if(num_spaces_removed != NULL){
			*num_spaces_removed = spaces_to_remove;
		}
		
		return SUCCESS;
	}
}

int center(const char *source, int width, char *result) {

	int i, cnt = 0, len = strlen(source);
	int spaces = (width - len) / 2;

	if(source == NULL || len == 0 || width < len){
		return FAILURE;
	}

	for(i = 0; i < spaces; i++){
		result[i] = ' ';
	}

	for(i = spaces; i < spaces + len; i++){
		result[i] = source[cnt];
		cnt++;
	}


	for(i = spaces + len; i < (spaces * 2) + len; i++){
		result[i] = ' ';
	}
	
	result[i + 1] = '\0';
	
	return SUCCESS;
}
