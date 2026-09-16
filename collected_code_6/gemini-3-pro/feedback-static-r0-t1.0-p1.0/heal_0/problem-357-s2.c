#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
    int* elements;
    size_t size;
} Tuple;

int find_max_in_tuples(Tuple* tuples, size_t num_tuples, int* max_val) {
    if (tuples == NULL || num_tuples == 0 || max_val == NULL) {
        return -1;
    }

    int current_max = INT_MIN;
    int found = 0;

    for (size_t i = 0; i < num_tuples; ++i) {
        if (tuples[i].elements == NULL || tuples[i].size == 0) {
            continue;
        }
        for (size_t j = 0; j < tuples[i].size; ++j) {
            if (tuples[i].elements[j] > current_max) {
                current_max = tuples[i].elements[j];
                found = 1;
            }
        }
    }

    if (!found) {
        return -1;
    }

    *max_val = current_max;
    return 0;
}

int main(void) {
    int elems1[] = {1, 5, 3};
    int elems2[] = {10, -2, 8};
    int elems3[] = {7, 14, 2};

    Tuple tuples[3];
    
    tuples[0].elements = elems1;
    tuples[0].size = sizeof(elems1) / sizeof(elems1[0]);

    tuples[1].elements = elems2;
    tuples[1].size = sizeof(elems2) / sizeof(elems2[0]);

    tuples[2].elements = elems3;
    tuples[2].size = sizeof(elems3) / sizeof(elems3[0]);

    int max_val = 0;
    if (find_max_in_tuples(tuples, 3, &max_val) == 0) {
        printf("Max element: %d\n", max_val);
    } else {
        printf("Failed to find max element or input was empty.\n");
    }

    return 0;
}