#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *first;
    int second;
} Tuple;

int compare_tuples(const void *a, const void *b) {
    const Tuple *t1 = (const Tuple *)a;
    const Tuple *t2 = (const Tuple *)b;
    return strcmp(t1->first, t2->first);
}

void sort_tuples(Tuple *tuples, size_t count) {
    if (tuples == NULL || count == 0) {
        return;
    }
    qsort(tuples, count, sizeof(Tuple), compare_tuples);
}

int main(void) {
    size_t count = 5;
    Tuple *tuples = (Tuple *)malloc(count * sizeof(Tuple));
    if (tuples == NULL) {
        return 1;
    }

    tuples[0].first = strdup("zebra");
    tuples[0].second = 5;
    tuples[1].first = strdup("apple");
    tuples[1].second = 2;
    tuples[2].first = strdup("mango");
    tuples[2].second = 9;
    tuples[3].first = strdup("banana");
    tuples[3].second = 4;
    tuples[4].first = strdup("cherry");
    tuples[4].second = 7;

    for (size_t i = 0; i < count; i++) {
        if (tuples[i].first == NULL) {
            for (size_t j = 0; j < i; j++) {
                free(tuples[j].first);
            }
            free(tuples);
            return 1;
        }
    }

    sort_tuples(tuples, count);

    for (size_t i = 0; i < count; i++) {
        printf("(%s, %d)\n", tuples[i].first, tuples[i].second);
    }

    for (size_t i = 0; i < count; i++) {
        free(tuples[i].first);
    }
    free(tuples);

    return 0;
}