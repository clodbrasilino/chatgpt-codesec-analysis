#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *first;
    int second;
} Tuple;

int compare(const void *a, const void *b) {
    return strcmp(((Tuple *)a)->first, ((Tuple *)b)->first);
}

void sort_tuples(Tuple *tuples, size_t n) {
    qsort(tuples, n, sizeof(Tuple), compare);
}

int main() {
    Tuple tuples[] = {
        {"banana", 2},
        {"apple", 1},
        {"orange", 3}
    };
    size_t n = sizeof(tuples) / sizeof(tuples[0]);

    sort_tuples(tuples, n);

    for (size_t i = 0; i < n; i++) {
        printf("(%s, %d)\n", tuples[i].first, tuples[i].second);
    }

    return 0;
}