#include <stdio.h>

void matchWords(const char** words, int length) {
  for (int i = 0; i < length; i++) {
    if (words[i][0] == 'p') {
      printf("%s\n", words[i]);
    }
  }
}

int main() {
  const char* wordList[] = {"apple", "banana", "pear", "peach", "orange"};

  matchWords(wordList, sizeof(wordList) / sizeof(wordList[0]));

  return 0;
}