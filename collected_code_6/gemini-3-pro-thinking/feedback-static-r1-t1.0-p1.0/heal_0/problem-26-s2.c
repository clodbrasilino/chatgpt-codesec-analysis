#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int first;
    int second;
} Tuple;

bool has_all_k_elements(const Tuple *tuples, size_t size, int k) {
    if (k < 0) {
        return false;
    }
    if (k == 0) {
        return true;
    }
    if (tuples == NULL) {
        return false;
    }

    bool *found = (bool *)calloc((size_t)k, sizeof(bool));
    if (found == NULL) {
        return false;
    }

    for (size_t i = 0; i < size; ++i) {
        if (tuples[i].first >= 0 && tuples[i].first < k) {
            found[tuples[i].first] = true;
        }
        if (tuples[i].second >= 0 && tuples[i].second < k) {
            found[tuples[i].second] = true;
        }
    }

    bool all_found = true;
    for (int i = 0; i < k; ++i) {
        if (!found[i]) {
            all_found = false;
            break;
        }
    }

    free(found);
    return all_found;
}

int main(void) {
    Tuple tuples[] = {
        {0, 1},
        {2, 3},
        {4, 1}
    };
    
    size_t size = sizeof(tuples) / sizeof(tuples[0]);
    int k = 5;

    bool result = has_all_k_elements(tuples, size, k);
    
    if (result) {
        printf("Success: All %d elements are present.\n", k);
    } else {
        printf("Failure: Not all %d elements are present.\n", k);
    }

    return EXIT_SUCCESS;
}