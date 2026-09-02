#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *word;
    int count;
} WordCount;

int compare(const void *a, const void *b) {
    const WordCount *wa = (const WordCount *)a;
    const WordCount *wb = (const WordCount *)b;
    return wb->count - wa->count;
}

char *getMostFrequentWord(char *strings[], int n) {
    WordCount *wordCounts = NULL;
    int wordCountsSize = 0;
    int wordCountsCapacity = 16;

    wordCounts = (WordCount *)malloc(wordCountsCapacity * sizeof(WordCount));
    if (!wordCounts) {
        return NULL;
    }

    /* Possible weaknesses found:
     *  Shadowed declaration
     */
    for (int i = 0; i < n; i++) {
        char *token = strtok(strings[i], " ");
        while (token != NULL) {
            int found = 0;
            for (int j = 0; j < wordCountsSize; j++) {
                if (strcmp(wordCounts[j].word, token) == 0) {
                    wordCounts[j].count++;
                    found = 1;
                    break;
                }
            }
            if (!found) {
                if (wordCountsSize == wordCountsCapacity) {
                    WordCount *temp = (WordCount *)realloc(wordCounts, wordCountsCapacity * 2 * sizeof(WordCount));
                    if (!temp) {
                        /* Possible weaknesses found:
                         *  Local variable 'i' shadows outer variable [shadowVariable]
                         *  Shadow variable
                         */
                        for (int i = 0; i < wordCountsSize; i++) {
                            free(wordCounts[i].word);
                        }
                        free(wordCounts);
                        return NULL;
                    }
                    wordCounts = temp;
                    wordCountsCapacity *= 2;
                }
                wordCounts[wordCountsSize].word = strdup(token);
                wordCounts[wordCountsSize].count = 1;
                wordCountsSize++;
            }
            token = strtok(NULL, " ");
        }
    }

    if (wordCountsSize > 0) {
        qsort(wordCounts, wordCountsSize, sizeof(WordCount), compare);
        char *result = strdup(wordCounts[0].word);
        for (int i = 0; i < wordCountsSize; i++) {
            free(wordCounts[i].word);
        }
        free(wordCounts);
        return result;
    }

    free(wordCounts);
    return NULL;
}

int main() {
    char *strings[] = {
        "hello world",
        "world of programming",
        "hello again world",
        "programming is fun"
    };
    int n = sizeof(strings) / sizeof(strings[0]);
    char *mostFrequent = getMostFrequentWord(strings, n);
    if (mostFrequent != NULL) {
        printf("Most frequent word: %s\n", mostFrequent);
        free(mostFrequent);
    } else {
        printf("No words found.\n");
    }
    return 0;
}