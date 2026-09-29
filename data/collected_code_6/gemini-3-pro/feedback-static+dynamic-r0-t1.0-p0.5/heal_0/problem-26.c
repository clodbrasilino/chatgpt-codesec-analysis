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

    for (size_t i = 0; i < list->size; ++i) {
        for (size_t j = 0; j < list->tuples[i].size; ++j) {
            int val = list->tuples[i].elements[j];
            if (val >= 1 && val <= k) {
                found[val] = true;
            }
        }
    }

    bool all_found = true;
    for (int i = 1; i <= k; ++i) {
        if (!found[i]) {
            all_found = false;
            break;
        }
    }

    free(found);
    return all_found;
}

int main(void) {
    int k = 3;
    
    int t1_data[] = {1, 5};
    int t2_data[] = {2, 3};
    
    Tuple tuples[2];
    tuples[0].elements = t1_data;
    tuples[0].size = 2;
    tuples[1].elements = t2_data;
    tuples[1].size = 2;
    
    TupleList list;
    list.tuples = tuples;
    list.size = 2;
    
    if (has_all_k_elements(&list, k)) {
        printf("All elements from 1 to %d are present.\n", k);
    } else {
        printf("Not all elements from 1 to %d are present.\n", k);
    }
    
    return 0;
}