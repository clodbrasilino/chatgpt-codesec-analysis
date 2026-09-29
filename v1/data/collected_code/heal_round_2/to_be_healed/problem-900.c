#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int startsWithNumber(const char* str, int number) {
   if (str == NULL) {
      return 0;
   }
   
   /* Possible weaknesses found:
    *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
    */
   int len = strlen(str);
   
   if (len == 0 || len == 1) {
      return 0;
   }
   
   if (isdigit(str[0])) {
      int firstDigit = str[0] - '0';
      
      if (firstDigit == number) {
         return 1;
      }
   }
   
   return 0;
}

int main() {
    char* str = "123456";
    int number = 1;

    int result = startsWithNumber(str, number);

    return 0;
}