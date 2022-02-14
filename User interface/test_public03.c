#include <stdio.h>
#include <string.h>
#include "document.h"

int main() {
   Document doc;
   const char *doc_name = "Testing Document";

   init_document(&doc, doc_name);

   /* Adding first paragraph */
   add_paragraph_after(&doc, 0);

   add_paragraph_after(&doc, 1);
   append_line(&doc, 1, " first line, first paragraph");
   append_line(&doc, 1, " second line, first paragraph");
   append_line(&doc, 2, " first line, second paragraph");
   print_document(&doc);
   printf("\n");
   remove_line(&doc, 1, 1);
   print_document(&doc);
   printf("\n");
   replace_text(&doc, ", fir", " XyZ");
   highlight_text(&doc, " first");
   print_document(&doc);
   printf("\n");
   return 0;
}
