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

    for (int i = 0; i < n; i++) {
        if (counts[i].count > 0) {
            if (i + 1 < n && counts[i + 1].count > 0) {
                free(counts);
                /* Possible weaknesses found:
                 * ASan: heap-use-after-free
                 */
                return counts[i + 1].str;
            }
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