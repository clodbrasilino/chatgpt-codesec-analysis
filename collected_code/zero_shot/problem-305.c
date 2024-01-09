#include <stdio.h>
#include <string.h>

void matchWords(char** words, int length) {
  for (int i = 0; i < length; i++) {
    if (words[i][0] == 'p') {
      printf("%s\n", words[i]);
    }
  }
}

int main() {
  char* wordList[] = {"apple", "banana", "pear", "peach", "orange"};

  matchWords(wordList, sizeof(wordList) / sizeof(wordList[0]));

  return 0;
}