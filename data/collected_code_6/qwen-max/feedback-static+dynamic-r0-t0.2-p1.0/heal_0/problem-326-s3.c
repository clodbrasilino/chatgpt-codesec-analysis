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

char* mostFrequentWord(char *strings[], int size) {
    if (size == 0) return NULL;

    WordCount *counts = (WordCount *)malloc(size * sizeof(WordCount));
    if (counts == NULL) return NULL;

    for (int i = 0; i < size; ++i) {
        counts[i].word = strings[i];
        counts[i].count = 1;
    }

    for (int i = 0; i < size; ++i) {
        for (int j = i + 1; j < size; ++j) {
            if (strcmp(strings[i], strings[j]) == 0) {
                counts[i].count++;
                counts[j].word = NULL;
            }
        }
    }

    qsort(counts, size, sizeof(WordCount), compare);

    for (int i = 0; i < size; ++i) {
        if (counts[i].word != NULL) {
            char *result = strdup(counts[i].word);
            free(counts);
            return result;
        }
    }

    free(counts);
    return NULL;
}

int main() {
    char *strings[] = {"apple", "banana", "apple", "orange", "banana", "apple"};
    int size = sizeof(strings) / sizeof(strings[0]);

    char *mostFrequent = mostFrequentWord(strings, size);
    if (mostFrequent != NULL) {
        printf("Most frequent word: %s\n", mostFrequent);
        free(mostFrequent);
    } else {
        printf("No words found.\n");
    }

    return 0;
}