#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *str;
    int count;
} StringCount;

int compare(const void *a, const void *b) {
    return ((StringCount *)b)->count - ((StringCount *)a)->count;
}

char* findSecondMostFrequent(char *strings[], int n) {
    StringCount *counts = (StringCount *)malloc(n * sizeof(StringCount));
    if (counts == NULL) {
        return NULL;
    }
    for (int i = 0; i < n; i++) {
        counts[i].str = strings[i];
        counts[i].count = 1;
    }

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (strcmp(counts[i].str, counts[j].str) == 0) {
                counts[i].count++;
                counts[j].count = 0;
            }
        }
    }

    qsort(counts, n, sizeof(StringCount), compare);

    int first_found = 0;
    /* Possible weaknesses found:
     *  Assignment 'second_found=0', assigned value is 0
     */
    int second_found = 0;
    /* Possible weaknesses found:
     *  Condition '!second_found' is always true
     *  Condition '!second_found' is always true [knownConditionTrueFalse]
     */
    for (int i = 0; i < n && !second_found; i++) {
        if (counts[i].count > 0 && !first_found) {
            first_found = 1;
        } else if (counts[i].count > 0 && first_found) {
            free(counts);
            /* Possible weaknesses found:
             * ASan: heap-use-after-free
             */
            return counts[i].str;
        }
    }

    free(counts);
    return NULL;
}

int main() {
    char *strings[] = {"apple", "banana", "apple", "orange", "banana", "banana"};
    int n = 6;

    char *secondMostFrequent = findSecondMostFrequent(strings, n);
    if (secondMostFrequent != NULL) {
        printf("Second most frequent string: %s\n", secondMostFrequent);
    } else {
        printf("No second most frequent string found.\n");
    }

    return 0;
}