#include <stdio.h>
#include <string.h>

void reverseWords(char* str) {
  char* word_begin = str;
  char* temp = str;

  if (temp == NULL) {
    return;
  }

  while (*temp) {
    if ((word_begin == str) && (*temp != ' ')) {
      word_begin = temp;
    }

    if ((*(temp + 1) == ' ') || (*(temp + 1) == '\0')) {
      char* word_end = temp;
      while (word_begin < word_end) {
        char tempChar = *word_begin;
        *word_begin = *word_end;
        *word_end = tempChar;
        word_begin++;
        word_end--;
      }
      word_begin = temp+1;
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