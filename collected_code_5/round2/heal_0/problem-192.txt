#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include <stdio.h>

bool hasLetterAndNumber(const char *str) {
   bool hasLetter = false, hasNumber = false;

   while (*str) {
      if (isalpha(*str)) hasLetter = true;
      else if (isdigit(*str)) hasNumber = true;

      if(hasLetter && hasNumber) return true;

      str++;
   }

   return false;
}

int main() {
    
    char string1[] = "Abc123";
    char string2[] = "123456";
    
    printf("%s contains atleast one letter and one number: %d\n", string1, hasLetterAndNumber(string1));
    printf("%s contains atleast one letter and one number: %d\n", string2, hasLetterAndNumber(string2));

    return 0;
}