#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int *elements;
    size_t size;
} Tuple;

bool has_all_k_elements(const Tuple *tuples, size_t num_tuples, int k) {
    if (tuples == NULL || k <= 0 || num_tuples == 0) {
        return false;
    }

    bool *found = (bool *)calloc((size_t)k, sizeof(bool));
    if (found == NULL) {
        return false;
    }

    for (size_t i = 0; i < num_tuples; i++) {
        if (tuples[i].elements == NULL) {
            continue;
        }
        for (size_t j = 0; j < tuples[i].size; j++) {
            int val = tuples[i].elements[j];
            if (val >= 1 && val <= k) {
                found[val - 1] = true;
            }
        }
    }

    bool all_present = true;
    for (int i = 0; i < k; i++) {
        if (!found[i]) {
            all_present = false;
            break;
        }
    }

    free(found);
    return all_present;
}

int main(void) {
    int t1_data[] = {1, 2};
    int t2_data[] = {3};
    int t3_data[] = {4, 5};

    Tuple tuples[3];
    tuples[0].elements = t1_data;
    tuples[0].size = 2;
    
    tuples[1].elements = t2_data;
    tuples[1].size = 1;
    
    tuples[2].elements = t3_data;
    tuples[2].size = 2;

    int k = 5;
    size_t num_tuples = 3;

    bool result = has_all_k_elements(tuples, num_tuples, k);

    if (result) {
        printf("All elements from 1 to %d are present.\n", k);
    } else {
        printf("Not all elements from 1 to %d are present.\n", k);
    }

    return 0;
}