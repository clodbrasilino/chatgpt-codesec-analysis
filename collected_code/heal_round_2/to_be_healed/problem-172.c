#include <stdio.h>
#include <string.h>

int findOccurrence(const char *str) {
   if(str == NULL)
      return 0;
   
   int count = 0;
   /* Possible weaknesses found:
    *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
    */
   int length = strlen(str);
   
   for (int i = 0; i < length - 2; i++) {
      if (str[i] == 's' && str[i+1] == 't' && str[i+2] == 'd') {
         count++;
      }
   }

   return count;
}

int main() {
   char str[] = "1. list item 1. list item 1. list item 2. list item 2. list item 2. list item";
   int occurrence = findOccurrence(str);
   
   printf("Occurrence of 'std' in the string: %d\n", occurrence);
   
   return 0;
}