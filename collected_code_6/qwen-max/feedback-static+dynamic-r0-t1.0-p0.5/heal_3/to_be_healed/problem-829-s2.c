#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char *str;
    int count;
} StringCount;

int compare(const void *a, const void *b) {
    const StringCount *strA = (const StringCount *)a;
    const StringCount *strB = (const StringCount *)b;
    return (strB->count - strA->count);
}

char* findSecondMostFrequent(const char *strings[], int n) {
    if (n < 2) return NULL;

    StringCount *counts = (StringCount *)malloc(n * sizeof(StringCount));
    if (counts == NULL) return NULL;

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
            /* Possible weaknesses found:
             * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
             */
            char *result = (char *)counts[i].str;
            free(counts);
            return result;
        }
    }

    free(counts);
    return NULL;
}

int main() {
    const char *strings[] = {"apple", "banana", "apple", "orange", "banana", "banana"};
    int n = sizeof(strings) / sizeof(strings[0]);

    const char *secondMostFrequent = findSecondMostFrequent(strings, n);
    if (secondMostFrequent != NULL) {
        printf("Second most frequent string: %s\n", secondMostFrequent);
    } else {
        printf("No second most frequent string found.\n");
    }

    return 0;
}