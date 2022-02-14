#include <stdio.h>
#include <string.h>
#include "text_manipulation.h"

void test_assert(int test_result, const char *test_name, int test_number) {
   if (test_result)  {
      printf("pass %s %d\n", test_name, test_number);
   } else {
      printf("fail %s %d\n", test_name, test_number);
   }
}

int main() {
   char result[MAX_STR_LEN + 1];
   int spaces_removed, test_result;

   remove_spaces("   bruh ", result, &spaces_removed);
  
   printf("%d", (int)strlen(result));
   /*printf("%s", result);*/
   printf("%d\n", spaces_removed);
   test_result = strcmp(result, "bruh bruh hm time") == 17 && spaces_removed == 4;
   test_assert(test_result, "remove_spaces", 2);

   return 0;
}

