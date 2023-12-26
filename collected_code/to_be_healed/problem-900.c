#include <string.h>
 /* Possible weaknesses found:
  *  include '<ctype.h>' or provide a declaration of 'isdigit'
  */

int startsWithNumber(const char* str, int number) {
   /* Possible weaknesses found:
    *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
    */
   int len = strlen(str);
   
   // Check if the string is empty or has only a single character
   if (len == 0 || len == 1) {
      return 0;
   }
   
   // Check if the first character is a digit
   /* Possible weaknesses found:
    *  implicit declaration of function 'isdigit' [-Wimplicit-function-declaration]
    */
   if (isdigit(str[0])) {
      // Convert the first character to an integer
      int firstDigit = str[0] - '0';
      
      // Check if the first digit matches the specified number
      if (firstDigit == number) {
         return 1;
      }
   }
   
   return 0;
}