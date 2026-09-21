#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORDS 1000
#define MAX_WORD_LEN 100

typedef struct {
    char *word;
    int count;
} WordCount;

int compareWords(const void *a, const void *b) {
    const WordCount *wordA = (const WordCount *)a;
    const WordCount *wordB = (const WordCount *)b;
    if (wordB->count != wordA->count) {
        return (wordB->count - wordA->count);
    }
    return strcmp(wordA->word, wordB->word);
}

void addOrIncrement(WordCount *wordArray, int *arraySize, const char *word) {
    for (int i = 0; i < *arraySize; ++i) {
        if (strcmp(wordArray[i].word, word) == 0) {
            wordArray[i].count++;
            return;
        }
    }
    if (*arraySize < MAX_WORDS) {
        size_t len = strnlen(word, MAX_WORD_LEN - 1);
        if (len > 0 && len < MAX_WORD_LEN) {
            wordArray[*arraySize].word = malloc((len + 1) * sizeof(char));
            if (wordArray[*arraySize].word) {
                memcpy(wordArray[*arraySize].word, word, len);
                wordArray[*arraySize].word[len] = '\0';
                wordArray[*arraySize].count = 1;
                (*arraySize)++;
            }
        }
    }
}

void processText(WordCount *wordArray, int *arraySize, const char *text) {
    char *token, *copy;
    const char *delimiters = " \t\n\r\f,.-:;!?()[]{}";
    copy = strdup(text);
    token = strtok(copy, delimiters);
    while (token != NULL) {
        size_t len = strnlen(token, MAX_WORD_LEN - 1);
        if (len > 0 && len < MAX_WORD_LEN)
            addOrIncrement(wordArray, arraySize, token);
        token = strtok(NULL, delimiters);
    }
    free(copy);
}

void freeWordArray(WordCount *wordArray, int arraySize) {
    for (int i = 0; i < arraySize; ++i) {
        free(wordArray[i].word);
    }
}

int main() {
    WordCount wordCounts[MAX_WORDS] = {0};
    int wordCountSize = 0;

    const char text[] = "This is a test. This test is only a test. Testing, one, two, three. Test test test.";
    processText(wordCounts, &wordCountSize, text);

    qsort(wordCounts, wordCountSize, sizeof(WordCount), compareWords);

    for (int i = 0; i < wordCountSize && wordCounts[i].count > 0; ++i) {
        printf("%s: %d\n", wordCounts[i].word, wordCounts[i].count);
    }

    freeWordArray(wordCounts, wordCountSize);

    return 0;
}