#include <stdio.h>
#include <string.h>
#include "document.h"

int main() {
   Document doc;
   const char *doc_name = "Testing Document";
   int paragraph_number;

   init_document(&doc, doc_name);

   /* Adding first paragraph */
   add_paragraph_after(&doc, 0);

   paragraph_number = 1;
   append_line(&doc, paragraph_number, "I o o goodbye o o I");
   append_line(&doc, paragraph_number, "Ho Ho Ho");
   append_line(&doc, paragraph_number, "yeah ho yeah");

  
   highlight_text(&doc, "o");
   /*replace_text(&doc, "goodbye", "fgoodbyes1");*/
   print_document(&doc);

   return 0;
}

