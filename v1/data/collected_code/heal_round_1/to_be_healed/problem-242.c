#include <stdio.h>

int countCharacters(char *str) {
   int count = 0;
   
   /* Possible weaknesses found:
    *  Cannot determine that '*str' is initialized [premium-bughuntingUninit]
    */
   while (*str != '\0') {
      count++;
      str++;
   }
   
   return count;
}

int main() {
   /* Possible weaknesses found:
    *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
    */
   char str[100];
   
   printf("Enter a string: ");
   /* Possible weaknesses found:
    *  Cannot determine that 'str[0]' is initialized [premium-bughuntingUninit]
    */
   fgets(str, sizeof(str), stdin);
   
   int totalCharacters = countCharacters(str);
   
   printf("Total characters in the string: %d", totalCharacters);
   
   return 0;
}