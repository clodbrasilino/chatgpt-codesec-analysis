#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    char *key;
    int frequency;
} Tuple;

int tuple_compare(const void *a, const void *b) {
    return strcmp(((Tuple *)a)->key, ((Tuple *)b)->key);
}

void assign_frequencies(Tuple *tuples, size_t tuple_count) {
    if (tuple_count == 0) return;
    qsort(tuples, tuple_count, sizeof(Tuple), tuple_compare);

    for (size_t i = 0; i < tuple_count; ++i) {
        if (i == 0 || strcmp(tuples[i].key, tuples[i - 1].key) != 0) {
            tuples[i].frequency = 1;
        } else {
            tuples[i].frequency = tuples[i - 1].frequency + 1;
        }
    }
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
    size_t tuple_count = sizeof(tuples) / sizeof(tuples[0]);

    assign_frequencies(tuples, tuple_count);

    for (size_t i = 0; i < tuple_count; ++i) {
        printf("%s: %d\n", tuples[i].key, tuples[i].frequency);
    }

    return 0;
}