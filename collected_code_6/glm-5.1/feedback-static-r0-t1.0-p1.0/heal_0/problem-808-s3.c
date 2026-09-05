#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int *elements;
    size_t size;
} Tuple;

bool tuple_contains_k(const Tuple *tuples, size_t num_tuples, int k) {
    if (tuples == NULL) {
        return false;
    }

    for (size_t i = 0; i < num_tuples; i++) {
        if (tuples[i].elements == NULL) {
            continue;
        }

        for (size_t j = 0; j < tuples[i].size; j++) {
            if (tuples[i].elements[j] == k) {
                return true;
            }
        }
    }

    return false;
}

int main(void) {
    int a1[] = {1, 2, 3};
    int a2[] = {4, 5, 6};
    int a3[] = {7, 8, 9};

    Tuple tuples[] = {
        {a1, sizeof(a1) / sizeof(a1[0])},
        {a2, sizeof(a2) / sizeof(a2[0])},
        {a3, sizeof(a3) / sizeof(a3[0])}
    };

    size_t num_tuples = sizeof(tuples) / sizeof(tuples[0]);
    int k = 5;

    if (tuple_contains_k(tuples, num_tuples, k)) {
        printf("%d found in tuples.\n", k);
    } else {
        printf("%d not found in tuples.\n", k);
    }

    return 0;
}