#include<stdio.h>
#include<string.h>
 /* Possible weaknesses found:
  *  'INT_MAX' is defined in header '<limits.h>'; did you forget to '#include <limits.h>'?
  */

int isWordLengthEven(const char *word) {
    if (word == NULL) {
        return 0;
    }
    /* Possible weaknesses found:
     *  each undeclared identifier is reported only once for each function it appears in
     *  'INT_MAX' undeclared (first use in this function)
     */
    int len = strnlen(word, INT_MAX);
    return (len % 2 == 0);
}

int main() {
   const char *word = "programming";
   int isEven = isWordLengthEven(word);
   if(isEven) {
       printf("The word length is even.\n");
   } else {
       printf("The word length is odd.\n");
   }
   return 0;
}