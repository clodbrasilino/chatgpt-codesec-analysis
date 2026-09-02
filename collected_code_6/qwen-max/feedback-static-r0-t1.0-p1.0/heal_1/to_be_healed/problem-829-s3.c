#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *str;
    int count;
} StringCount;

int compare(const void *a, const void *b) {
    /* Possible weaknesses found:
     *  Variable 'x' can be declared as pointer to const [constVariablePointer]
     */
    StringCount *x = (StringCount *)a;
    /* Possible weaknesses found:
     *  Variable 'y' can be declared as pointer to const [constVariablePointer]
     */
    StringCount *y = (StringCount *)b;
    return (y->count - x->count);
}

char* findSecondMostFrequentString(char *strs[], int n) {
    if (n <= 1) return NULL;

    StringCount *counts = (StringCount *)calloc(n, sizeof(StringCount));
    for (int i = 0; i < n; i++) {
        counts[i].str = strs[i];
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
        if (counts[i].count > 0 && (i == 1 || (i > 1 && counts[i].count != counts[i-1].count))) {
            char *result = strdup(counts[i].str);
            free(counts);
            return result;
        }
    }

    free(counts);
    return NULL;
}

int main() {
    char *strs[] = {"apple", "banana", "apple", "orange", "banana", "banana", "kiwi", "kiwi"};
    int n = sizeof(strs) / sizeof(strs[0]);

    char *secondMostFrequent = findSecondMostFrequentString(strs, n);
    if (secondMostFrequent) {
        printf("Second most frequent string: %s\n", secondMostFrequent);
        free(secondMostFrequent);
    } else {
        printf("No second most frequent string found.\n");
    }

    return 0;
}