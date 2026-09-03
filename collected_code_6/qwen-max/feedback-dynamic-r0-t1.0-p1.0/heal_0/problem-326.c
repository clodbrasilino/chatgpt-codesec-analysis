#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *word;
    int count;
} WordCount;

int compare(const void *a, const void *b) {
    return ((WordCount *)b)->count - ((WordCount *)a)->count;
}

char* findMostFrequentWord(char *strings[], int n) {
    if (n == 0) return NULL;

    WordCount *wordCounts = (WordCount *)malloc(n * sizeof(WordCount));
    for (int i = 0; i < n; ++i) {
        wordCounts[i].word = strings[i];
        wordCounts[i].count = 1;
    }

    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (strcmp(strings[i], strings[j]) == 0) {
                wordCounts[i].count++;
                wordCounts[j].count = 0; // Mark as counted
            }
        }
    }

    qsort(wordCounts, n, sizeof(WordCount), compare);

    char *result = wordCounts[0].word;
    free(wordCounts);
    return result;
}

int main() {
    char *strings[] = {"apple", "banana", "apple", "orange", "banana", "apple"};
    int n = sizeof(strings) / sizeof(strings[0]);

    char *mostFrequent = findMostFrequentWord(strings, n);
    if (mostFrequent) {
        printf("The most frequent word is: %s\n", mostFrequent);
    } else {
        printf("No words provided.\n");
    }

    return 0;
}