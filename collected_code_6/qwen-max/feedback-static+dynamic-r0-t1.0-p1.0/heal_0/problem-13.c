#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORDS 1000
#define MAX_WORD_LEN 100

typedef struct {
    char word[MAX_WORD_LEN];
    int count;
} WordCount;

int compareWords(const void *a, const void *b) {
    WordCount *wordA = (WordCount *)a;
    WordCount *wordB = (WordCount *)b;
    return (wordB->count - wordA->count);
}

void addOrIncrement(WordCount *wordArray, int *arraySize, const char *word) {
    for (int i = 0; i < *arraySize; ++i) {
        if (strcmp(wordArray[i].word, word) == 0) {
            wordArray[i].count++;
            return;
        }
    }
    if (*arraySize < MAX_WORDS) {
        strncpy(wordArray[*arraySize].word, word, MAX_WORD_LEN-1);
        wordArray[*arraySize].count = 1;
        (*arraySize)++;
    }
}

void processText(WordCount *wordArray, int *arraySize, const char *text) {
    char *token;
    const char *delimiters = " \t\n\r\f,.-:;!?()[]{}";
    token = strtok((char *)text, delimiters);
    while (token != NULL) {
        if (strlen(token) > 0)
            addOrIncrement(wordArray, arraySize, token);
        token = strtok(NULL, delimiters);
    }
}

int main() {
    WordCount wordCounts[MAX_WORDS] = {0};
    int wordCountSize = 0;

    char text[] = "This is a test. This test is only a test. Testing, one, two, three. Test test test.";
    processText(wordCounts, &wordCountSize, text);

    qsort(wordCounts, wordCountSize, sizeof(WordCount), compareWords);

    for (int i = 0; i < wordCountSize && wordCounts[i].count > 0; ++i) {
        printf("%s: %d\n", wordCounts[i].word, wordCounts[i].count);
    }

    return 0;
}