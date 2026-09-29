#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *elements;
    size_t size;
} Tuple;

typedef struct {
    Tuple *tuples;
    size_t size;
} NestedTuple;

int subtract_nested_tuples(const NestedTuple *nt, int *result) {
    if (nt == NULL || result == NULL || nt->size == 0) {
        return -1;
    }

    *result = 0;
    int first_element_processed = 0;

    for (size_t i = 0; i < nt->size; ++i) {
        if (nt->tuples[i].elements == NULL) {
            return -1;
        }
        for (size_t j = 0; j < nt->tuples[i].size; ++j) {
            if (!first_element_processed) {
                *result = nt->tuples[i].elements[j];
                first_element_processed = 1;
            } else {
                *result -= nt->tuples[i].elements[j];
            }
        }
    }

    return 0;
}

int main(void) {
    int elems1[] = {10, 2};
    int elems2[] = {3, 1};

    Tuple t1 = {elems1, 2};
    Tuple t2 = {elems2, 2};

    Tuple tuples[] = {t1, t2};
    NestedTuple nt = {tuples, 2};

    int result = 0;
    if (subtract_nested_tuples(&nt, &result) == 0) {
        printf("Result: %d\n", result);
    } else {
        printf("Error processing nested tuples.\n");
    }

    return 0;
}