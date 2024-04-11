#include <stdio.h>
#include <string.h>

int matchWords(char* word1, char* word2, char** wordList, int listSize) {
    int i;
    int match1 = 0, match2 = 0;
    for(i = 0; i < listSize; i++) {
        if(wordList[i][0] == 'p' || wordList[i][0] == 'P') {
            if(strcmp(wordList[i], word1) == 0) {
                match1 = 1;
            }
            if(strcmp(wordList[i], word2) == 0) {
                match2 = 1;
            }
        }
    }
    return match1 && match2;
}

int main() {
    char* wordList[] = {"pear", "apple", "peach", "grape", "pineapple"};
    int listSize = sizeof(wordList) / sizeof(wordList[0]);
    char* word1 = "pear";
    char* word2 = "pineapple";

    if(matchWords(word1, word2, wordList, listSize)) {
        printf("Both words are found in the list and start with 'p'.\n");
    } else {
        printf("Both words are not found in the list or do not start with 'p'.\n");
    }

    return 0;
}