#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>

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
        wordCounts[i].word = NULL;
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

    if (textLen >= SIZE_MAX - 1) {
        return -1;
    }

    char *textCopy = (char *)calloc(textLen + 1, sizeof(char));
    if (textCopy == NULL) {
        return -1;
    }

    if (textLen + 1 > textLen) {
        memcpy(textCopy, text, textLen);
        textCopy[textLen] = '\0';
    } else {
        free(textCopy);
        return -1;
    }

    int wordCount = 0;
    char *saveptr = NULL;
    char *token = strtok_r(textCopy, " \t\n\r.,;:!?\"'()[]{}", &saveptr);

    while (token != NULL && wordCount < maxWords) {
        for (size_t i = 0; token[i]; i++) {
            token[i] = (char)tolower((unsigned char)token[i]);
        }

        size_t tokenLen = strnlen(token, MAX_WORD_LENGTH - 1);
        if (tokenLen >= MAX_WORD_LENGTH - 1) {
            token = strtok_r(NULL, " \t\n\r.,;:!?\"'()[]{}", &saveptr);
            continue;
        }

        int found = 0;
        for (int i = 0; i < wordCount; i++) {
            if (wordCounts[i].word != NULL && strncmp(wordCounts[i].word, token, MAX_WORD_LENGTH) == 0) {
                wordCounts[i].count++;
                found = 1;
                break;
            }
        }

        if (!found) {
            char *wordCopy = (char *)calloc(tokenLen + 1, sizeof(char));
            if (wordCopy == NULL) {
                free(textCopy);
                freeWordCounts(wordCounts, wordCount);
                return -1;
            }
            if (tokenLen + 1 > tokenLen) {
                memcpy(wordCopy, token, tokenLen);
                wordCopy[tokenLen] = '\0';
            } else {
                free(wordCopy);
                free(textCopy);
                freeWordCounts(wordCounts, wordCount);
                return -1;
            }

            wordCounts[wordCount].word = wordCopy;
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
    char *text = (char *)calloc(MAX_TEXT_SIZE, sizeof(char));
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
        printf("%d. %s: %d\n", i + 1, wordCounts[i].word, wordCounts[i].count);
    }

    freeWordCounts(wordCounts, count);
    free(text);
    free(wordCounts);

    return 0;
}