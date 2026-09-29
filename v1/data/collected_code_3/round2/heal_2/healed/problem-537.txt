#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_WORD_LEN 100

char* findFirstRepeatedWord(char* str) {
    char* word = (char*)malloc(MAX_WORD_LEN);
    char* words[100];
    int i, j = 0, k = 0, w = 0;

    if (word == NULL) {
        return NULL;
    }

    for(i = 0; i <= strlen(str); i++) {
        if(str[i] == ' ' || str[i] == '\0') {
            word[j] = '\0';
            for(k = 0; k < w; k++) {
                if(strcmp(words[k], word) == 0) {
                    char *result = strdup(word);
                    for(int l = 0; l < w; l++) {
                        free(words[l]);
                    }
                    free(word);
                    return result;
                }
            }
            words[w] = (char*)malloc(strlen(word) + 1);
            if(words[w] == NULL) {
                for(int l = 0; l < w; l++) {
                    free(words[l]);
                }
                free(word);
                return NULL;
            }
            strcpy(words[w], word);
            w++;
            j = 0;
        } else {
            word[j++] = str[i];
        }
    }
    for(i = 0; i < w; i++) {
        free(words[i]);
    }
    free(word);
    return NULL;
}

int main() {
    char str[] = "This is a test string for testing";
    char* word = findFirstRepeatedWord(str);
    if(word != NULL) {
        printf("First repeated word: %s\n", word);
        free(word);
    } else {
        printf("No repeated words found\n");
    }
    return 0;
}