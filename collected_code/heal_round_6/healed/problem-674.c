#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_WORDS 100
#define MAX_WORD_LEN 256

void removeDuplicates(char *string) {
    char wordArray[MAX_WORDS][MAX_WORD_LEN];
    int wordCount = 0;
    char *temp = malloc(sizeof(char) * MAX_WORD_LEN);

    if(temp == NULL) {
        fprintf(stderr, "Failed to allocate memory\n");
        return;
    }

    char *word = strtok(string, " ");
    while (word != NULL && wordCount < MAX_WORDS) {
        int exists = 0;
        for (int i = 0; i < wordCount; i++) {
            if (strcmp(wordArray[i], word) == 0) {
                exists = 1;
                break;
            }
        }
        if (!exists) {
            strncpy(wordArray[wordCount], word, MAX_WORD_LEN - 1);
            wordArray[wordCount][MAX_WORD_LEN - 1] = '\0';
            wordCount++;
        }
        word = strtok(NULL, " ");
    }

    if(wordCount > 0) {
        snprintf(temp, MAX_WORD_LEN, "%s", wordArray[0]);
        for (int i = 1; i < wordCount; i++) {
            snprintf(temp + strlen(temp), MAX_WORD_LEN - strlen(temp), " %s", wordArray[i]);
        }
        strncpy(string, temp, MAX_WORD_LEN);
        string[MAX_WORD_LEN - 1] = '\0';
    }
    free(temp);
}

int main() {
    char str[MAX_WORD_LEN] = "This is a test test string to test remove duplicate duplicate words";
    removeDuplicates(str);
    printf("%s\n", str);
    return 0;
}