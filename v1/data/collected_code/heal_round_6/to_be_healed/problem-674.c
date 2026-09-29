#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_WORDS 100
#define MAX_WORD_LEN 256

void removeDuplicates(char *string) {
    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
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
            if (strncmp(wordArray[i], word, MAX_WORD_LEN - 1) == 0) {
                exists = 1;
                break;
            }
        }
        if (!exists) {
            /* Possible weaknesses found:
             *   Easily used incorrectly; doesn't always \0-terminate or check for invalid  pointers [MS-banned] (CWE-120).
             */
            strncpy(wordArray[wordCount], word, MAX_WORD_LEN - 1);
            wordArray[wordCount][MAX_WORD_LEN - 1] = '\0';
            wordCount++;
        }
        word = strtok(NULL, " ");
    }

    if(wordCount > 0) {
        snprintf(temp, MAX_WORD_LEN, "%s", wordArray[0]);
        for (int i = 1; i < wordCount; i++) {
            /* Possible weaknesses found:
             *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
             */
            snprintf(temp + strlen(temp), MAX_WORD_LEN - strlen(temp), " %s", wordArray[i]);
        }
        /* Possible weaknesses found:
         *   Easily used incorrectly; doesn't always \0-terminate or check for invalid  pointers [MS-banned] (CWE-120).
         */
        strncpy(string, temp, MAX_WORD_LEN);
        string[MAX_WORD_LEN - 1] = '\0';
    }
    free(temp);
}

int main() {
    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    char str[MAX_WORD_LEN] = "This is a test test string to test remove duplicate duplicate words";
    removeDuplicates(str);
    printf("%s\n", str);
    return 0;
}