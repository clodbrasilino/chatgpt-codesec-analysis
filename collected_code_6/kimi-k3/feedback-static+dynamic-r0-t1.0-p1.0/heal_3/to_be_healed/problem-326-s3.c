#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORD_LENGTH 100
#define MAX_WORDS 1000

typedef struct {
    char *word;
    int count;
} WordCount;

int findWordIndex(WordCount *wordCounts, int wordCountSize, const char *word) {
    for (int i = 0; i < wordCountSize; i++) {
        if (strcmp(wordCounts[i].word, word) == 0) {
            return i;
        }
    }
    return -1;
}

char *getMostFrequentWord(char **strings, int stringsCount) {
    if (strings == NULL || stringsCount <= 0) {
        return NULL;
    }

    WordCount *wordCounts = calloc(MAX_WORDS, sizeof(WordCount));
    if (wordCounts == NULL) {
        return NULL;
    }

    int wordCountSize = 0;

    for (int i = 0; i < stringsCount; i++) {
        if (strings[i] == NULL) {
            continue;
        }

        size_t len = strnlen(strings[i], MAX_WORD_LENGTH * MAX_WORDS);
        char *tempString = malloc(len + 1);
        if (tempString == NULL) {
            for (int j = 0; j < wordCountSize; j++) {
                free(wordCounts[j].word);
            }
            free(wordCounts);
            return NULL;
        }
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(tempString, strings[i], len);
        tempString[len] = '\0';

        char *token = strtok(tempString, " \t\n\r");
        while (token != NULL) {
            if (strnlen(token, MAX_WORD_LENGTH) >= MAX_WORD_LENGTH) {
                token = strtok(NULL, " \t\n\r");
                continue;
            }

            int index = findWordIndex(wordCounts, wordCountSize, token);
            if (index != -1) {
                wordCounts[index].count++;
            } else {
                if (wordCountSize < MAX_WORDS) {
                    /* Possible weaknesses found:
                     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
                     */
                    wordCounts[wordCountSize].word = malloc(strlen(token) + 1);
                    if (wordCounts[wordCountSize].word == NULL) {
                        free(tempString);
                        for (int j = 0; j < wordCountSize; j++) {
                            free(wordCounts[j].word);
                        }
                        free(wordCounts);
                        return NULL;
                    }
                    /* Possible weaknesses found:
                     * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
                     */
                    strcpy(wordCounts[wordCountSize].word, token);
                    wordCounts[wordCountSize].count = 1;
                    wordCountSize++;
                }
            }
            token = strtok(NULL, " \t\n\r");
        }

        free(tempString);
    }

    if (wordCountSize == 0) {
        free(wordCounts);
        return NULL;
    }

    int maxIndex = 0;
    for (int i = 1; i < wordCountSize; i++) {
        if (wordCounts[i].count > wordCounts[maxIndex].count) {
            maxIndex = i;
        }
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t resultLen = strlen(wordCounts[maxIndex].word) + 1;
    char *result = malloc(resultLen);
    if (result == NULL) {
        for (int j = 0; j < wordCountSize; j++) {
            free(wordCounts[j].word);
        }
        free(wordCounts);
        return NULL;
    }
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(result, wordCounts[maxIndex].word, resultLen);

    for (int j = 0; j < wordCountSize; j++) {
        free(wordCounts[j].word);
    }
    free(wordCounts);
    return result;
}

int main(void) {
    char *strings[] = {
        "hello world hello",
        "world of programming",
        "hello programming world",
        "the quick brown fox",
        "hello hello world"
    };
    int stringsCount = sizeof(strings) / sizeof(strings[0]);

    char *mostFrequent = getMostFrequentWord(strings, stringsCount);

    if (mostFrequent != NULL) {
        printf("Most frequent word: %s\n", mostFrequent);
        free(mostFrequent);
    } else {
        printf("No words found or error occurred.\n");
    }

    return 0;
}