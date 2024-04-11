#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORD_LENGTH 50
#define MAX_WORDS 1000

typedef struct {
    char word[MAX_WORD_LENGTH];
    int count;
} WordCount;

int get_word_index(WordCount wordCounts[], int numWords, char* word) {
    for (int i = 0; i < numWords; i++) {
        if (strcmp(wordCounts[i].word, word) == 0) {
            return i;
        }
    }
    return -1;
}

void count_words(char* words[], int numWords, WordCount wordCounts[], int* numWordCounts) {
    for (int i = 0; i < numWords; i++) {
        int index = get_word_index(wordCounts, *numWordCounts, words[i]);
        if (index == -1) {
            strcpy(wordCounts[*numWordCounts].word, words[i]);
            wordCounts[*numWordCounts].count = 1;
            (*numWordCounts)++;
        } else {
            wordCounts[index].count++;
        }
    }
}

void print_most_common_words(WordCount wordCounts[], int numWordCounts) {
    int maxCount = 0;
    for (int i = 0; i < numWordCounts; i++) {
        if (wordCounts[i].count > maxCount) {
            maxCount = wordCounts[i].count;
        }
    }
    for (int i = 0; i < numWordCounts; i++) {
        if (wordCounts[i].count == maxCount) {
            printf("%s: %d\n", wordCounts[i].word, wordCounts[i].count);
        }
    }
}

int main() {
    char* words[MAX_WORDS] = {"apple", "banana", "apple", "orange", "banana", "banana", "grape"};
    int numWords = 7;
    WordCount wordCounts[MAX_WORDS];
    int numWordCounts = 0;

    count_words(words, numWords, wordCounts, &numWordCounts);
    print_most_common_words(wordCounts, numWordCounts);

    return 0;
}