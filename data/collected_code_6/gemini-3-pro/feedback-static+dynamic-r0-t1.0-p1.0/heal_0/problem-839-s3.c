#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *first;
    char *second;
} Tuple;

int compare_tuples(const void *a, const void *b) {
    const Tuple *tuple_a = (const Tuple *)a;
    const Tuple *tuple_b = (const Tuple *)b;
    return strcmp(tuple_a->first, tuple_b->first);
}

void sort_tuples(Tuple *tuples, size_t count) {
    if (tuples == NULL || count == 0) {
        return;
    }
    qsort(tuples, count, sizeof(Tuple), compare_tuples);
}

int main(void) {
    Tuple tuples[] = {
        {"zebra", "animal"},
        {"apple", "fruit"},
        {"banana", "fruit"},
        {"carrot", "vegetable"}
    };
    
    size_t count = sizeof(tuples) / sizeof(tuples[0]);
    
    sort_tuples(tuples, count);
    
    for (size_t i = 0; i < count; i++) {
        if (printf("(%s, %s)\n", tuples[i].first, tuples[i].second) < 0) {
            return EXIT_FAILURE;
        }
    }
    
    return EXIT_SUCCESS;
}