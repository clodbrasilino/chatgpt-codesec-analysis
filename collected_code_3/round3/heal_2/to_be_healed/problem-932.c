#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORD_SIZE 100
#define MAX_WORDS 1000

int isDuplicate(char* word, char** newWords, int newNumWords) {
    for(int i = 0; i < newNumWords; i++) {
        if(strcmp(word, newWords[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

void removeDuplicates(char** words, int* numWords) {
    char** newWords = (char**)malloc(sizeof(char*) * MAX_WORDS);
    int newNumWords = 0;

    if(!newWords) {
        return;
    }     

    for(int i = 0; i < *numWords; i++) {
        if(!isDuplicate(words[i], newWords, newNumWords)) {
            newWords[newNumWords] = (char*)malloc(sizeof(char) * MAX_WORD_SIZE);
            if(!newWords[newNumWords]) continue;
            strcpy(newWords[newNumWords], words[i]);
            newNumWords++;
        }
    }

    for(int i = 0; i < *numWords; i++) {
        free(words[i]);
    }
    free(words);

    *numWords = newNumWords;

    for (int i = 0; i < *numWords; i++) {
        /* Possible weaknesses found:
         *  use after 'free' of 'words' [CWE-416] [-Wanalyzer-use-after-free]
         */
        words[i] = newWords[i];
    }
    free(newWords);
}

int main() {
    int numWords = 5;
    char** words = (char**)malloc(sizeof(char*) * numWords);

    if(!words) {
        return -1;
    }

    for(int i = 0; i < numWords; i++) {
        words[i] = (char*)malloc(sizeof(char) * MAX_WORD_SIZE);
        if(!words[i]) return -1;
    }

    strcpy(words[0], "Hello");
    strcpy(words[1], "World");
    strcpy(words[2], "Hello");
    strcpy(words[3], "Hello");
    strcpy(words[4], "World");

    removeDuplicates(words, &numWords);

    for(int i = 0; i < numWords; i++) {
        printf("%s\n", words[i]);
        free(words[i]);
    }
    free(words);

    return 0;
}