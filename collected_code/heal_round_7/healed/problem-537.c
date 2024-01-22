#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* findFirstRepeatedWord(char* str) {
    if(!str || *str == '\0') {
        return NULL;
    }

    size_t len = strlen(str);
    char *temp = (char *)calloc(len + 1, sizeof(char));
    if(!temp) {
        printf("Memory allocation failed\n");
        return NULL;
    }

    memcpy(temp, str, len);
    temp[len] = '\0';

    char **words = (char **)calloc(100, sizeof(char*));
    if(!words) {
        printf("Memory allocation failed\n");
        free(temp);
        return NULL;
    }

    int i = 0;
    words[i] = strtok(temp, " ");
    while (words[i] != NULL) {
        for(int j = 0; j < i; j++) {
            if (strcmp(words[j], words[i]) == 0) {
                char *duplicate_word = strdup(words[i]);
                if(!duplicate_word) {
                    printf("Memory allocation failed\n");
                    free(temp);
                    free(words);
                    return NULL;
                }
                free(temp);
                free(words);
                return duplicate_word;
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