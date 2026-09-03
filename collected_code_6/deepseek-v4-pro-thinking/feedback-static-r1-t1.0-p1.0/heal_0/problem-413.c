#include <stdio.h>
#include <stddef.h>

#define TUPLE_SIZE 3

typedef struct {
    int values[TUPLE_SIZE];
} Tuple;

int extract_nth_element(const Tuple *tuples, size_t tuple_count, size_t n, int *results, size_t results_capacity) {
    if (tuples == NULL || results == NULL || n >= TUPLE_SIZE || results_capacity < tuple_count) {
        return -1;
    }

    for (size_t i = 0; i < tuple_count; ++i) {
        results[i] = tuples[i].values[n];
    }

    return 0;
}

int main(void) {
    Tuple tuples[] = {
        {{1, 2, 3}},
        {{4, 5, 6}},
        {{7, 8, 9}}
    };
    size_t tuple_count = sizeof(tuples) / sizeof(tuples[0]);
    int results[3];

    if (extract_nth_element(tuples, tuple_count, 1, results, tuple_count) != 0) {
        return 1;
    }

    for (size_t i = 0; i < tuple_count; ++i) {
        printf("%d\n", results[i]);
    }

    return 0;
}