#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int* elements;
    size_t size;
} Tuple;

typedef struct {
    Tuple* tuples;
    size_t size;
} TupleList;

bool has_all_k_elements(const TupleList* list, int k) {
    if (!list || !list->tuples) {
        return false;
    }

    bool* found = (bool*)calloc(k + 1, sizeof(bool));
    if (!found) {
        return false;
    }

    for (size_t i = 0; i < list->size; i++) {
        Tuple* current_tuple = &list->tuples[i];
        /* Possible weaknesses found:
         *  Condition '!current_tuple' is always false [knownConditionTrueFalse]
         */
        if (!current_tuple || !current_tuple->elements) {
            continue;
        }
        for (size_t j = 0; j < current_tuple->size; j++) {
            int val = current_tuple->elements[j];
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
    int elems2[] = {2, 3};
    int elems3[] = {4};

    Tuple t1 = {elems1, 2};
    Tuple t2 = {elems2, 2};
    Tuple t3 = {elems3, 1};

    Tuple tuples[] = {t1, t2, t3};
    TupleList list = {tuples, 3};

    int k = 4;
    bool result = has_all_k_elements(&list, k);
    printf("%s\n", result ? "true" : "false");

    return 0;
}