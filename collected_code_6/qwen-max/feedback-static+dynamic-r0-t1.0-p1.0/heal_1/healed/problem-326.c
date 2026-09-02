#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct WordCount {
    char *word;
    int count;
} WordCount;

int compare(const void *a, const void *b) {
    return ((WordCount *)b)->count - ((WordCount *)a)->count;
}

char* findMostFrequentWord(char *strings[], int size) {
    WordCount *wordCounts = NULL;
    int capacity = 10, length = 0;
    wordCounts = malloc(capacity * sizeof(WordCount));
    if (wordCounts == NULL) return NULL;

    for (int i = 0; i < size; i++) {
        char *strCopy = strdup(strings[i]);
        if (strCopy == NULL) {
            free(wordCounts);
            return NULL;
        }
        char *token = strtok(strCopy, " ");
        while (token != NULL) {
            int found = 0;
            for (int j = 0; j < length; j++) {
                if (strcmp(wordCounts[j].word, token) == 0) {
                    wordCounts[j].count++;
                    found = 1;
                    break;
                }
            }
            if (!found) {
                if (length >= capacity) {
                    capacity *= 2;
                    WordCount *newArray = realloc(wordCounts, capacity * sizeof(WordCount));
                    if (newArray == NULL) {
                        free(wordCounts);
                        for (int k = 0; k < length; k++) {
                            free(wordCounts[k].word);
                        }
                        free(strCopy);
                        return NULL;
                    }
                    wordCounts = newArray;
                }
                wordCounts[length].word = strdup(token);
                if (wordCounts[length].word == NULL) {
                    for (int k = 0; k < length; k++) {
                        free(wordCounts[k].word);
                    }
                    free(wordCounts);
                    free(strCopy);
                    return NULL;
                }
                wordCounts[length].count = 1;
                length++;
            }
            token = strtok(NULL, " ");
        }
        free(strCopy);
    }

    qsort(wordCounts, length, sizeof(WordCount), compare);

    char *mostFrequentWord = strdup(wordCounts[0].word);
    for (int i = 0; i < length; i++) {
        free(wordCounts[i].word);
    }
    free(wordCounts);

    return mostFrequentWord;
}

int main() {
    char *strings[] = {
        "hello world",
        "world of code",
        "hello again and again"
    };
    int size = sizeof(strings) / sizeof(strings[0]);

    char *mostFrequent = findMostFrequentWord(strings, size);
    if (mostFrequent != NULL) {
        printf("Most frequent word: %s\n", mostFrequent);
        free(mostFrequent);
    } else {
        printf("No words found.\n");
    }

    return 0;
}