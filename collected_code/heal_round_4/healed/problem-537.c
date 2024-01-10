#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* findFirstRepeatedWord(char* str) {
    char *temp, **words;
    int i, j;

    if(str == NULL) {
        return NULL;
    }

    size_t len = strlen(str);
    temp = (char*)calloc(len + 1, sizeof(char));
    if(temp == NULL) {
        printf("Memory allocation failed\n");
        return NULL;
    }

    strncpy(temp, str, len);

    words = calloc(100, sizeof(char*));
    if(words == NULL) {
        printf("Memory allocation failed\n");
        free(temp);
        return NULL;
    }

    i = 0;
    words[i] = strtok(temp, " ");
    while (words[i] != NULL) {
        for (j = 0; j < i; j++) {
            if (strcmp(words[j], words[i]) == 0) {
                words[i] = strdup(words[i]);
                if(words[i] == NULL) {
                    printf("Memory allocation failed\n");
                    free(temp);
                    free(words);
                    return NULL;
                }
                free(temp);
                return words[i];
            }
        }

        i++;
        words[i] = strtok(NULL, " ");
    }

    free(temp);
    free(words);
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