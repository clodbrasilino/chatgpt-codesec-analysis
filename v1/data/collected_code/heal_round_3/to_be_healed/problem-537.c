#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* findFirstRepeatedWord(char* str) {
    char *word, *temp;
    char* words[100] = {NULL};
    int i = 0;

    /* Possible weaknesses found:
     *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
     */
    temp = (char*)malloc(strlen(str)+1);
    if(temp == NULL) {
        printf("Memory allocation failed\n");
        return NULL;
    }

    /* Possible weaknesses found:
     *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
     *   Easily used incorrectly; doesn't always \0-terminate or check for invalid  pointers [MS-banned] (CWE-120).
     */
    strncpy(temp, str, strlen(str)+1);
    
    word = strtok(temp, " ");

    while (word != NULL) {
        for (int j = 0; j < i; j++) {
            if (strcmp(words[j], word) == 0) {
                word = strdup(word); // because we are going to free "temp"
                if(word == NULL) {
                    printf("Memory allocation failed\n");
                    free(temp);
                    return NULL;
                }
                free(temp);
                return word;
            }
        }

        words[i++] = word;
        word = strtok(NULL, " ");
    }

    free(temp);
    return NULL;
}

int main() {
    char str[] = "This is a sample string with repeated words";
    char* repeatedWord = findFirstRepeatedWord(str);

    if (repeatedWord != NULL) {
        printf("First repeated word: %s\n", repeatedWord);
        free(repeatedWord);
    } else {
        printf("No repeated word found\n");
    }

    return 0;
}