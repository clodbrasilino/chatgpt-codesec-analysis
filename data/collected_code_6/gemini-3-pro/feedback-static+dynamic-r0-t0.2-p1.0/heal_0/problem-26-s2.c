#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int *elements;
    size_t size;
} Tuple;

typedef struct {
    Tuple *tuples;
    size_t size;
} TupleList;

bool has_all_k_elements(const TupleList *list, int k) {
    if (!list || !list->tuples || k <= 0) {
        return false;
    }

    bool *found = (bool *)calloc(k + 1, sizeof(bool));
    if (!found) {
        return false;
    }

    for (size_t i = 0; i < list->size; i++) {
        for (size_t j = 0; j < list->tuples[i].size; j++) {
            int val = list->tuples[i].elements[j];
            if (val >= 1 && val <= k) {
                found[val] = true;
            }
        }
    }

    bool all_found = true;
    for (int i = 1; i <= k; i++) {
        if (!found[i]) {
            all_found = false;
            break;
        }
    }

    free(found);
    return all_found;
}

int main(void) {
    int elems1[] = {1, 2};
    int elems2[] = {3, 4};
    int elems3[] = {5, 1};

    Tuple tuples[] = {
        {elems1, 2},
        {elems2, 2},
        {elems3, 2}
    };

    TupleList list = {tuples, 3};

    int k = 5;
    bool result = has_all_k_elements(&list, k);

    if (result) {
        printf("All elements from 1 to %d are present.\n", k);
    } else {
        printf("Not all elements from 1 to %d are present.\n", k);
    }

    return 0;
}