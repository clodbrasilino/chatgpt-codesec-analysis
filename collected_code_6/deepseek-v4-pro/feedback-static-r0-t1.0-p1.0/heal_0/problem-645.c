#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int *elements;
    size_t length;
} Tuple;

bool get_kth_product(Tuple *tuples, size_t tuple_count, size_t k, int *result) {
    if (tuples == NULL || result == NULL) {
        return false;
    }
    if (tuple_count == 0) {
        return false;
    }
    for (size_t i = 0; i < tuple_count; i++) {
        if (tuples[i].elements == NULL) {
            return false;
        }
        if (k >= tuples[i].length) {
            return false;
        }
    }

    int product = 1;
    for (size_t i = 0; i < tuple_count; i++) {
        product *= tuples[i].elements[k];
    }
    *result = product;
    return true;
}

int main(void) {
    int t1_data[] = {2, 3, 4};
    int t2_data[] = {5, 6, 7};
    int t3_data[] = {1, 2, 3};

    Tuple tuples[3];
    tuples[0].elements = t1_data;
    tuples[0].length = 3;
    tuples[1].elements = t2_data;
    tuples[1].length = 3;
    tuples[2].elements = t3_data;
    tuples[2].length = 3;

    size_t k = 1;
    int result = 0;

    if (get_kth_product(tuples, 3, k, &result)) {
        printf("%d\n", result);
    } else {
        printf("Error\n");
    }

    return 0;
}