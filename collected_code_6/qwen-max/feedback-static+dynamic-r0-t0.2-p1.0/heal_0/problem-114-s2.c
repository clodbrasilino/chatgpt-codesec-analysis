#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *key;
    int frequency;
} Tuple;

int compare(const void *a, const void *b) {
    return strcmp(((Tuple *)a)->key, ((Tuple *)b)->key);
}

void assignFrequency(Tuple *tuples, int n) {
    if (n <= 0) return;

    qsort(tuples, n, sizeof(Tuple), compare);

    int count = 1;
    for (int i = 1; i < n; ++i) {
        if (strcmp(tuples[i].key, tuples[i - 1].key) == 0) {
            ++count;
        } else {
            tuples[i - 1].frequency = count;
            count = 1;
        }
    }
    tuples[n - 1].frequency = count;
}

int main() {
    Tuple tuples[] = {
        {"apple", 0},
        {"banana", 0},
        {"apple", 0},
        {"orange", 0},
        {"banana", 0},
        {"apple", 0}
    };
    int n = sizeof(tuples) / sizeof(tuples[0]);

    assignFrequency(tuples, n);

    for (int i = 0; i < n; ++i) {
        printf("%s: %d\n", tuples[i].key, tuples[i].frequency);
    }

    return 0;
}