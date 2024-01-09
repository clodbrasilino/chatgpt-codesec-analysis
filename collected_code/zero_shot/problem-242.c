#include <stdio.h>

int countCharacters(char *str) {
   int count = 0;
   
   while (*str != '\0') {
      count++;
      str++;
   }
   
   return count;
}

int main() {
   char str[100];
   
   printf("Enter a string: ");
   fgets(str, sizeof(str), stdin);
   
   int totalCharacters = countCharacters(str);
   
   printf("Total characters in the string: %d", totalCharacters);
   
   return 0;
}