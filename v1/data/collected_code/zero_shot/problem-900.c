#include <string.h>

int startsWithNumber(const char* str, int number) {
   int len = strlen(str);
   
   // Check if the string is empty or has only a single character
   if (len == 0 || len == 1) {
      return 0;
   }
   
   // Check if the first character is a digit
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