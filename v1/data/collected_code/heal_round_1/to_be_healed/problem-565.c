#include<stdio.h>
#include<string.h>

void splitString(char str[]) {
   /* Possible weaknesses found:
    *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
    *  Cannot determine that 'str[0]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
    */
   int length = strlen(str);
   
   printf("Individual characters: ");

   for(int i = 0; i < length; i++) {
      printf("%c ", str[i]);
   }
}

int main() {
   /* Possible weaknesses found:
    *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
    */
   char input[100];
   
   printf("Enter a string: ");
   /* Possible weaknesses found:
    *  Cannot determine that 'input[0]' is initialized [premium-bughuntingUninit]
    */
   fgets(input, sizeof(input), stdin);

   // Removing newline character from fgets input
   /* Possible weaknesses found:
    *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
    */
   if (input[strlen(input)-1] == '\n')
      /* Possible weaknesses found:
       *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
       */
      input[strlen(input)-1] = '\0';
   
   splitString(input);
   
   return 0;
}