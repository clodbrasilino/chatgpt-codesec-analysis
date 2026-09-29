#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORD_LENGTH 50
#define MAX_WORDS 1000

typedef struct {
    char word[MAX_WORD_LENGTH];
    int count;
} WordCount;

int find_word(WordCount *wordCounts, int numWords, char *word) {
    for (int i = 0; i < numWords; i++) {
        if (strcmp(wordCounts[i].word, word) == 0) {
            return i;
        }
    }
    return -1;
}

void count_words(char *text, WordCount *wordCounts, int *numWords) {
    char *word = strtok(text, " ");
    while (word != NULL) {
        int index = find_word(wordCounts, *numWords, word);
        if (index == -1) {
            strcpy(wordCounts[*numWords].word, word);
            wordCounts[*numWords].count = 1;
            (*numWords)++;
        } else {
            wordCounts[index].count++;
        }
        word = strtok(NULL, " ");
    }
}

void print_most_common_words(WordCount *wordCounts, int numWords) {
    int maxCount = 0;
    for (int i = 0; i < numWords; i++) {
        if (wordCounts[i].count > maxCount) {
            maxCount = wordCounts[i].count;
        }
    }
    for (int i = 0; i < numWords; i++) {
        if (wordCounts[i].count == maxCount) {
            printf("%s: %d\n", wordCounts[i].word, wordCounts[i].count);
        }
    }
}

int main() {
    char text[] = "the quick brown fox jumps over the lazy dog the quick brown fox jumps over the lazy dog";
    WordCount wordCounts[MAX_WORDS];
    int numWords = 0;

    count_words(text, wordCounts, &numWords);
    print_most_common_words(wordCounts, numWords);

    return 0;
}