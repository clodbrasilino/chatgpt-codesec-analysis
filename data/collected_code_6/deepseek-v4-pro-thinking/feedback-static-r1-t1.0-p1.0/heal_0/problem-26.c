#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Tuple;

bool has_all_k_elements(const Tuple *tuples, size_t tuple_count, int k) {
    if (k <= 0) {
        return true;
    }
    if (tuples == NULL && tuple_count > 0) {
        return false;
    }

    bool *seen = calloc((size_t)k, sizeof(*seen));
    if (seen == NULL) {
        return false;
    }

    for (size_t i = 0; i < tuple_count; ++i) {
        int values[2] = { tuples[i].first, tuples[i].second };
        for (size_t j = 0; j < 2; ++j) {
            if (values[j] >= 1 && values[j] <= k) {
                seen[values[j] - 1] = true;
            }
        }
    }

    bool result = true;
    for (int i = 0; i < k; ++i) {
        if (!seen[i]) {
            result = false;
            break;
        }
    }

    free(seen);
    return result;
}

int main(void) {
    Tuple tuples[] = {
        {1, 2},
        {3, 4},
        {5, 2}
    };
    size_t tuple_count = sizeof(tuples) / sizeof(tuples[0]);
    int k = 5;

    if (has_all_k_elements(tuples, tuple_count, k)) {
        puts("true");
    } else {
        puts("false");
    }

    return 0;
}