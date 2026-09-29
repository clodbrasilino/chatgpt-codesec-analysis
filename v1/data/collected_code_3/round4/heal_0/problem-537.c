#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_WORD_LENGTH 100

char* findFirstRepeatedWord(char* str) {
    char* token;
    char* words[MAX_WORD_LENGTH];
    int i, j = 0;

    token = strtok(str, " ");
    while (token != NULL) {
        for (i = 0; i < j; i++) {
            if (strcmp(words[i], token) == 0) {
                return token;
            }
        }
        words[j] = token;
        j++;
        token = strtok(NULL, " ");
    }
    return NULL;
}

int main() {
    char str[] = "This is a test. This is only a test.";
    char* result = findFirstRepeatedWord(str);
    if (result) {
        printf("First repeated word: %s\n", result);
    } else {
        printf("No repeated words found.\n");
    }
    return 0;
}