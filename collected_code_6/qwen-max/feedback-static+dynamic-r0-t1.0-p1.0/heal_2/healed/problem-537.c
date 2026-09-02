#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX_WORDS 1024
#define MAX_WORD_LENGTH 64

char* findFirstRepeatedWord(const char* str) {
    if (str == NULL) return NULL;

    char words[MAX_WORDS][MAX_WORD_LENGTH] = {0};
    int wordCount = 0;

    char* mutableStr = strdup(str);
    char* token = strtok(mutableStr, " .,;:!?-");
    while (token != NULL && wordCount < MAX_WORDS) {
        bool found = false;
        for (int i = 0; i < wordCount; ++i) {
            if (strcasecmp(words[i], token) == 0) {
                free(mutableStr);
                return strdup(token);
            }
        }
        if (!found) {
            strncpy(words[wordCount++], token, MAX_WORD_LENGTH - 1);
            words[wordCount - 1][MAX_WORD_LENGTH - 1] = '\0';
        }
        token = strtok(NULL, " .,;:!?-");
    }

    free(mutableStr);
    return NULL;
}

int main() {
    const char* str = "This is a test. This is only a test.";
    char* result = findFirstRepeatedWord(str);
    if (result) {
        printf("First repeated word: %s\n", result);
        free(result);
    } else {
        printf("No repeated word found.\n");
    }
    return 0;
}