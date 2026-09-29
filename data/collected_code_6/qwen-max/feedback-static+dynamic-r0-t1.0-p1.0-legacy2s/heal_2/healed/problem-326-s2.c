#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORDS 10000
#define MAX_WORD_LENGTH 100

typedef struct {
    char word[MAX_WORD_LENGTH];
    int count;
} WordCount;

int compare(const void *a, const void *b) {
    return ((WordCount *)b)->count - ((WordCount *)a)->count;
}

char* mostFrequentWord(const char *strings[], int size) {
    WordCount words[MAX_WORDS] = {0};
    int wordCount = 0;

    for (int i = 0; i < size; ++i) {
        char copy[MAX_WORD_LENGTH];
        strncpy(copy, strings[i], MAX_WORD_LENGTH - 1);
        copy[MAX_WORD_LENGTH - 1] = '\0';
        char *token = strtok(copy, " ");
        while (token) {
            int found = 0;
            for (int j = 0; j < wordCount; ++j) {
                if (strcmp(words[j].word, token) == 0) {
                    words[j].count++;
                    found = 1;
                    break;
                }
            }
            if (!found && wordCount < MAX_WORDS) {
                strncpy(words[wordCount].word, token, MAX_WORD_LENGTH - 1);
                words[wordCount].word[MAX_WORD_LENGTH - 1] = '\0';
                words[wordCount].count = 1;
                wordCount++;
            }
            token = strtok(NULL, " ");
        }
    }

    qsort(words, wordCount, sizeof(WordCount), compare);

    if (wordCount > 0) {
        return words[0].word;
    } else {
        return NULL;
    }
}

int main() {
    const char *strings[] = {
        "hello world",
        "hello again world",
        "hello there",
        "hello"
    };
    int size = 4;

    char *result = mostFrequentWord(strings, size);
    if (result) {
        printf("Most frequent word: %s\n", result);
    } else {
        printf("No words found.\n");
    }

    return 0;
}