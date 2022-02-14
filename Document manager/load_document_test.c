#include <stdio.h>
#include <string.h>
#include "document.h"

int main(){
	Document doc;
	const char *doc_name = "Loading Document";
	int data_lines = 4;
	char data1[20][MAX_STR_SIZE + 1] = {"1a", "1b", "", "1c"};
	char data2[20][MAX_STR_SIZE + 1] = {"2a", "2b", "", "2c"};
	init_document(&doc, doc_name);
	load_document(&doc, data1, data_lines);
	load_document(&doc, data2, data_lines);
	print_document(&doc);
	return 0;
}
