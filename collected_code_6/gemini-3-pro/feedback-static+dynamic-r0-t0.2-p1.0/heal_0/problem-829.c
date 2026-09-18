#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *str;
    int count;
} StringCount;

char* findSecondMostFrequent(char **sequence, int size) {
    if (sequence == NULL || size < 2) {
        return NULL;
    }

    StringCount *counts = (StringCount *)malloc(size * sizeof(StringCount));
    if (counts == NULL) {
        return NULL;
    }

    int uniqueCount = 0;

    for (int i = 0; i < size; i++) {
        if (sequence[i] == NULL) {
            continue;
        }
        int found = 0;
        for (int j = 0; j < uniqueCount; j++) {
            if (strcmp(counts[j].str, sequence[i]) == 0) {
                counts[j].count++;
                found = 1;
                break;
            }
        }
        if (!found) {
            counts[uniqueCount].str = sequence[i];
            counts[uniqueCount].count = 1;
            uniqueCount++;
        }
    }

    int firstMax = 0;
    int secondMax = 0;
    char *firstStr = NULL;
    char *secondStr = NULL;

    for (int i = 0; i < uniqueCount; i++) {
        if (counts[i].count > firstMax) {
            secondMax = firstMax;
            secondStr = firstStr;
            firstMax = counts[i].count;
            firstStr = counts[i].str;
        } else if (counts[i].count > secondMax && counts[i].count < firstMax) {
            secondMax = counts[i].count;
            secondStr = counts[i].str;
        }
    }

    free(counts);
    return secondStr;
}

int main(void) {
    char *sequence[] = {"apple", "banana", "apple", "orange", "banana", "apple", "grape", "banana", "grape"};
    int size = sizeof(sequence) / sizeof(sequence[0]);

    char *result = findSecondMostFrequent(sequence, size);

    if (result != NULL) {
        printf("%s\n", result);
    } else {
        printf("No second most frequent string found.\n");
    }

    return 0;
}