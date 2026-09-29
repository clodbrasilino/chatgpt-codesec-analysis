#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_WORD_LENGTH 50
#define MAX_WORDS 100

int isWordExist(char* word, char* words[], int count) {
    for(int i = 0; i < count; i++) {
        if(strcmp(words[i], word) == 0) {
            return 1;
        }
    }
    return 0;
}

char* removeDuplicateWords(char* str) {
    char* words[MAX_WORDS];
    int count = 0;

    char* word = strtok(str, " ");
    while(word != NULL) {
        if(!isWordExist(word, words, count)) {
            words[count] = malloc(strlen(word) + 1);
            strcpy(words[count++], word);
        }
        word = strtok(NULL, " ");
    }

    char* result = malloc(strlen(str) + 1);
    strcpy(result, words[0]);
    for(int i = 1; i < count; i++) {
        strcat(result, " ");
        strcat(result, words[i]);
        free(words[i]);
    }

    return result;
}

int main() {
    char str[] = "Hello world world Hello";
    char* result = removeDuplicateWords(str);
    printf("%s\n", result);
    free(result);
    return 0;
}