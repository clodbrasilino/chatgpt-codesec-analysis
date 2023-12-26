#include <stdio.h>
#include <string.h>

void matchWords(char** words, int length) {
  for (int i = 0; i < length; i++) {
    /* Possible weaknesses found:
     *  Cannot determine that 'words[i][0]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     */
    if (words[i][0] == 'p') {
      /* Possible weaknesses found:
       *  Cannot determine that 'words[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
       */
      printf("%s\n", words[i]);
    }
  }
}

int main() {
  char* wordList[] = {"apple", "banana", "pear", "peach", "orange"};

  matchWords(wordList, sizeof(wordList) / sizeof(wordList[0]));

  return 0;
}