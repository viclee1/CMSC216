#include <stdio.h>

int valid_character(char symbol);
int draw_rectangle(char symbol, int length, int width);
int draw_triangle(char symbol, int size);

int valid_character(char symbol){

        if(symbol == '*' || symbol == '%' || symbol == '#'){
                return 0;
        } else {
                return 1;
        }
}

/* draws rectangle if the proper input is given */
int draw_rectangle(char symbol, int length, int width){

	if(length == 0 || width == 0){
		printf("Invalid data provided.\n");
		return 0;
	} else {
		int i = 0, j = 0;
		for(i = 0; i < width; i++){
			for(j = 0; j < length; j++){
				printf("%c", symbol);
			}
			printf("\n");
		}
		return 1;
	}
}

/* draws pyramid style triangle if proper input is given */
int draw_triangle(char symbol, int size){

	if(size == 0){
		printf("Invalid data provided.\n");
		return 0;
	} else {
		int i = 1, j = 1, spaces = 1;
		for(i = 1; i <= size; i++) {

			/* makes spaces */
			for(spaces = 1; spaces <= size - i; spaces++) {
				printf(" ");
			}
			
			/* actual triangle format */
			for(j = 1; j <= ((i * 2) - 1); j++){
				printf("%c", symbol);
			}
			printf("\n");
		}
		return 1;
	}
}

int main(){

	int input_value = -1, quit = 0;
	char input_char = '*';

	do{
		printf("Enter 1(rectangle), 2(triangle), 3(other), 0(quit): ");
		scanf(" %d", &input_value);

		if(input_value == 1){
			int input_width = 0, input_length = 0;
			printf("Enter character, width and length: ");
			scanf(" %c%d%d", &input_char, &input_width, &input_length);
			if(valid_character(input_char)  == 1) {
				printf("Invalid data provided.\n");
			} else {
				draw_rectangle(input_char, input_length, input_width);
			}
		} else if(input_value == 2) {
			int input_size = 0;
			printf("Enter character and size: ");
			scanf(" %c%d", &input_char, &input_size);
			if(valid_character(input_char) == 1) {
				printf("Invalid data provided.\n");
			} else{
       				draw_triangle(input_char, input_size);
			}
		} else if(input_value == 3) {
			/* no plans on doing a third, so blank is left */
		} else if(input_value == 0) {
			quit = 1;
			printf("Bye Bye.\n");
		} else {
			printf("Invalid choice.\n");
		}
	} while(quit != 1);
	return 0;
}
