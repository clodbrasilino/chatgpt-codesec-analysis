#include<stdio.h>
#include<string.h>

#define MAX_INPUT 101

void splitString(const char str[]) {
   int length = strnlen(str, MAX_INPUT); 
   
   printf("Individual characters: ");

   for(int i = 0; i < length; i++) {
      printf("%c ", str[i]);
   }   
}

int main() {
   char input[MAX_INPUT];
      
   printf("Enter a string: ");
   fgets(input, sizeof(input), stdin);

   size_t inputLength = strnlen(input, sizeof(input));
   if(inputLength > 0 && input[inputLength - 1] == '\n'){
      input[inputLength - 1] = '\0';
   }

   splitString(input);
   
   return 0;
}