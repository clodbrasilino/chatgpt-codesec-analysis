#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct StringFrequency {
    char *str;
    int count;
};

void freeFrequencies(struct StringFrequency *freqs, int size) {
    if (freqs) {
        for (int i = 0; i < size; ++i) {
            free(freqs[i].str);
        }
        free(freqs);
    }
}

char* findSecondMostFrequent(char **seq, int size) {
    if (!seq || size < 2) {
        return NULL;
    }

    struct StringFrequency *freqs = calloc(size, sizeof(struct StringFrequency));
    if (!freqs) {
        return NULL;
    }

    int uniqueCount = 0;

    for (int i = 0; i < size; ++i) {
        if (!seq[i]) continue;
        
        int found = 0;
        for (int j = 0; j < uniqueCount; ++j) {
            if (strcmp(freqs[j].str, seq[i]) == 0) {
                freqs[j].count++;
                found = 1;
                break;
            }
        }

        if (!found) {
            freqs[uniqueCount].str = strdup(seq[i]);
            if (!freqs[uniqueCount].str) {
                freeFrequencies(freqs, uniqueCount);
                return NULL;
            }
            freqs[uniqueCount].count = 1;
            uniqueCount++;
        }
    }

    int firstMax = 0, secondMax = 0;
    char *firstStr = NULL, *secondStr = NULL;

    for (int i = 0; i < uniqueCount; ++i) {
        if (freqs[i].count > firstMax) {
            secondMax = firstMax;
            secondStr = firstStr;
            firstMax = freqs[i].count;
            firstStr = freqs[i].str;
        } else if (freqs[i].count > secondMax && freqs[i].count != firstMax) {
            secondMax = freqs[i].count;
            secondStr = freqs[i].str;
        }
    }

    char *result = NULL;
    if (secondStr) {
        result = strdup(secondStr);
    }

    freeFrequencies(freqs, uniqueCount);
    return result;
}

int main() {
    char *sequence[] = {"apple", "banana", "apple", "orange", "banana", "apple", "orange", "orange", "grape"};
    int size = sizeof(sequence) / sizeof(sequence[0]);

    char *secondMostFrequent = findSecondMostFrequent(sequence, size);

    if (secondMostFrequent) {
        printf("Second most frequent string: %s\n", secondMostFrequent);
        free(secondMostFrequent);
    } else {
        printf("No second most frequent string found.\n");
    }

    return 0;
}