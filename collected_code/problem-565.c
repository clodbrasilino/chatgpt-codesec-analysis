#include<stdio.h>
#include<string.h>

void splitString(char str[]) {
   int length = strlen(str);
   
   printf("Individual characters: ");

   for(int i = 0; i < length; i++) {
      printf("%c ", str[i]);
   }
}

int main() {
   char input[100];
   
   printf("Enter a string: ");
   fgets(input, sizeof(input), stdin);

   // Removing newline character from fgets input
   if (input[strlen(input)-1] == '\n')
      input[strlen(input)-1] = '\0';
   
   splitString(input);
   
   return 0;
}