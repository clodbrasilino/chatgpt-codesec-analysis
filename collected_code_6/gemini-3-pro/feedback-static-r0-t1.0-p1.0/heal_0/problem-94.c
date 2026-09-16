#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
    int index;
    int val1;
    int val2;
} Tuple;

int extract_min_index_record(const Tuple* tuples, size_t size, Tuple* out_min_tuple) {
    if (tuples == NULL || size == 0 || out_min_tuple == NULL) {
        return -1;
    }

    int min_val = INT_MAX;
    size_t min_idx = 0;
    int found = 0;

    for (size_t i = 0; i < size; ++i) {
        if (tuples[i].index < min_val) {
            min_val = tuples[i].index;
            min_idx = i;
            found = 1;
        }
    }

    if (found) {
        *out_min_tuple = tuples[min_idx];
        return 0;
    }

    return -1;
}

int main(void) {
    Tuple tuples[] = {
        {5, 10, 20},
        {2, 30, 40},
        {8, 50, 60},
        {1, 70, 80}
    };
    size_t num_tuples = sizeof(tuples) / sizeof(tuples[0]);

    Tuple min_tuple;
    if (extract_min_index_record(tuples, num_tuples, &min_tuple) == 0) {
        printf("Min index record: index=%d, val1=%d, val2=%d\n", 
               min_tuple.index, min_tuple.val1, min_tuple.val2);
    } else {
        printf("Failed to extract min index record.\n");
    }

    return 0;
}