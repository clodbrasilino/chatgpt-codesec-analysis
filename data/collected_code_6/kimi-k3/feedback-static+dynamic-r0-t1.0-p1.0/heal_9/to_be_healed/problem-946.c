#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_TEXT_SIZE 10000
#define MAX_WORDS 1000
#define MAX_WORD_LENGTH 100

typedef struct {
    char *word;
    int count;
} WordCount;

static void freeWordCounts(WordCount *wordCounts, int count) {
    if (wordCounts == NULL) {
        return;
    }
    for (int i = 0; i < count; i++) {
        free(wordCounts[i].word);
    }
}

int findMostCommonElements(const char *text, WordCount *wordCounts, int maxWords) {
    if (text == NULL || wordCounts == NULL || maxWords <= 0) {
        return -1;
    }

    size_t textLen = strnlen(text, MAX_TEXT_SIZE);
    if (textLen == 0 || textLen >= MAX_TEXT_SIZE) {
        return -1;
    }

    char *textCopy = (char *)malloc(textLen + 1);
    if (textCopy == NULL) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(textCopy, text, textLen);
    textCopy[textLen] = '\0';

    int wordCount = 0;
    char *saveptr = NULL;
    char *token = strtok_r(textCopy, " \t\n\r.,;:!?\"'()[]{}", &saveptr);

    while (token != NULL && wordCount < maxWords) {
        for (int i = 0; token[i]; i++) {
            token[i] = (char)tolower((unsigned char)token[i]);
        }

        int found = 0;
        for (int i = 0; i < wordCount; i++) {
            if (wordCounts[i].word != NULL && strcmp(wordCounts[i].word, token) == 0) {
                wordCounts[i].count++;
                found = 1;
                break;
            }
        }

        if (!found) {
            size_t tokenLen = strnlen(token, MAX_WORD_LENGTH);
            if (tokenLen >= MAX_WORD_LENGTH) {
                tokenLen = MAX_WORD_LENGTH - 1;
            }

            wordCounts[wordCount].word = (char *)malloc(tokenLen + 1);
            if (wordCounts[wordCount].word == NULL) {
                free(textCopy);
                freeWordCounts(wordCounts, wordCount);
                return -1;
            }

            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(wordCounts[wordCount].word, token, tokenLen);
            wordCounts[wordCount].word[tokenLen] = '\0';
            wordCounts[wordCount].count = 1;
            wordCount++;
        }

        token = strtok_r(NULL, " \t\n\r.,;:!?\"'()[]{}", &saveptr);
    }

    free(textCopy);
    return wordCount;
}

void sortByFrequency(WordCount *wordCounts, int count) {
    if (wordCounts == NULL || count <= 0) {
        return;
    }

    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (wordCounts[j].count < wordCounts[j + 1].count) {
                WordCount temp = wordCounts[j];
                wordCounts[j] = wordCounts[j + 1];
                wordCounts[j + 1] = temp;
            }
        }
    }
}

int main(void) {
    char *text = (char *)malloc(MAX_TEXT_SIZE);
    if (text == NULL) {
        fprintf(stderr, "Memory allocation error\n");
        return 1;
    }

    WordCount *wordCounts = (WordCount *)calloc(MAX_WORDS, sizeof(WordCount));
    if (wordCounts == NULL) {
        fprintf(stderr, "Memory allocation error\n");
        free(text);
        return 1;
    }

    printf("Enter text: ");
    if (fgets(text, MAX_TEXT_SIZE, stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        free(text);
        free(wordCounts);
        return 1;
    }

    size_t len = strnlen(text, MAX_TEXT_SIZE);
    if (len > 0 && text[len - 1] == '\n') {
        text[len - 1] = '\0';
    }

    int count = findMostCommonElements(text, wordCounts, MAX_WORDS);

    if (count < 0) {
        fprintf(stderr, "Error processing text\n");
        free(text);
        free(wordCounts);
        return 1;
    }

    if (count == 0) {
        printf("No words found in the text\n");
        free(text);
        free(wordCounts);
        return 0;
    }

    sortByFrequency(wordCounts, count);

    printf("\nMost common elements and their counts:\n");
    printf("--------------------------------------\n");

    int maxDisplay = (count < 10) ? count : 10;
    for (int i = 0; i < maxDisplay; i++) {
        if (wordCounts[i].word != NULL) {
            printf("%d. %s: %d\n", i + 1, wordCounts[i].word, wordCounts[i].count);
        }
    }

    freeWordCounts(wordCounts, count);
    free(wordCounts);
    free(text);

    return 0;
}