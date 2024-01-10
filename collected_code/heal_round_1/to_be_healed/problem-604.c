#include <stdio.h>
#include <string.h>

void reverseWords(char* str) {
  char* word_begin = NULL;
  char* temp = str;
 
  // Reverse individual words
  /* Possible weaknesses found:
   *  Cannot determine that '*temp' is initialized [premium-bughuntingUninit]
   */
  while (*temp) {
    // Find start of a word
    if ((word_begin == NULL) && (*temp != ' ')) {
      word_begin = temp;
    }
    // Find end of a word
    if (word_begin && ((*(temp + 1) == ' ') || (*(temp + 1) == '\0'))) {
      char* word_end = temp;
      // Reverse the word
      while (word_begin < word_end) {
        char tempChar = *word_begin;
        *word_begin = *word_end;
        *word_end = tempChar;
        word_begin++;
        word_end--;
      }
      word_begin = NULL;
    }
    temp++;
  }
}

int main() {
  char str[] = "Hello World!";

  printf("Original string: %s\n", str);

  reverseWords(str);

  printf("Reversed string: %s\n", str);

  return 0;
}