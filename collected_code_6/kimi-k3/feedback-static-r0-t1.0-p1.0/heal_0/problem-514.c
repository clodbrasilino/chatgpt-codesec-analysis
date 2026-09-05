#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *elements;
    size_t count;
} Tuple;

int sum_tuple(const Tuple *t, long *result) {
    size_t i;
    long sum = 0;

    if (t == NULL || result == NULL) {
        return -1;
    }

    if (t->count > 0 && t->elements == NULL) {
        return -1;
    }

    for (i = 0; i < t->count; i++) {
        sum += t->elements[i];
    }

    *result = sum;
    return 0;
}

int main(void) {
    Tuple tuples[3];
    int data1[] = {1, 2, 3};
    int data2[] = {4, 5};
    int data3[] = {6};
    size_t i;
    long result;

    tuples[0].elements = data1;
    tuples[0].count = 3;
    tuples[1].elements = data2;
    tuples[1].count = 2;
    tuples[2].elements = data3;
    tuples[2].count = 1;

    for (i = 0; i < 3; i++) {
        if (sum_tuple(&tuples[i], &result) == 0) {
            printf("Sum of tuple %zu: %ld\n", i, result);
        } else {
            fprintf(stderr, "Error computing sum for tuple %zu\n", i);
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}