#include <stdio.h>
#include <string.h>

int findOccurrence(const char *str, size_t str_length) {
   if(str == NULL || str_length == 0)
      return 0;
   
   int count = 0;
   int length = (int)str_length;

   if (length < 3)
      return count;

   for (int i = 0; i < length - 2; i++) {
      if (str[i] == 's' && str[i+1] == 't' && str[i+2] == 'd') {
         count++;
      }
   }

   return count;
}

int main() {
   char str[] = "1. list item 1. list item 1. list item 2. list item 2. list item 2. list item";
   int occurrence = findOccurrence(str, sizeof(str)/sizeof(str[0]) - 1);
   
   printf("Occurrence of 'std' in the string: %d\n", occurrence);
   
   return 0;
}