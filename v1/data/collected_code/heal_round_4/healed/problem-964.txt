#include <stdio.h>
#include <string.h>
#include <limits.h>

int isWordLengthEven(const char *word) {
    if (word == NULL) {
        return 0;
    }
    int len = strnlen(word, INT_MAX);
    return (len % 2 == 0);
}

int main() {
   const char *word = "programming";
   int isEven = isWordLengthEven(word);
   if(isEven) {
       printf("The word length is even.\n");
   } else {
       printf("The word length is odd.\n");
   }
   return 0;
}