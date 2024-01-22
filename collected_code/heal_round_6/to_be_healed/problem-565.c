#include<stdio.h>
#include<string.h>

#define MAX_INPUT 101

void splitString(const char str[], size_t strSize) {
   size_t length = strnlen(str, strSize);

   printf("Individual characters: ");

   for(size_t i = 0; i < length; i++) {
      printf("%c ", str[i]);
   }   
}

int main() {
   /* Possible weaknesses found:
    *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
    */
   char input[MAX_INPUT];
      
   printf("Enter a string: ");
   if(fgets(input, sizeof(input), stdin) != NULL) {

      size_t inputLength = strnlen(input, sizeof(input)-1);
      if(inputLength > 0 && input[inputLength - 1] == '\n'){
         input[inputLength - 1] = '\0';
      }

      splitString(input, sizeof(input));
   }
   
   return 0;
}