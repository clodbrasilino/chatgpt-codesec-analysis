#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
    int value;
} Tuple;

int extract_min_index(const Tuple *tuples, size_t count, size_t *min_index) {
    if (tuples == NULL || min_index == NULL || count == 0) {
        return -1;
    }

    int min_value = INT_MAX;
    size_t min_idx = 0;
    int found = 0;

    for (size_t i = 0; i < count; i++) {
        if (tuples[i].value < min_value) {
            min_value = tuples[i].value;
            min_idx = i;
            found = 1;
        }
    }

    if (!found) {
        return -1;
    }

    *min_index = min_idx;
    return 0;
}

int main(void) {
    Tuple tuples[] = {
        {10},
        {5},
        {20},
        {3},
        {15}
    };
    size_t count = sizeof(tuples) / sizeof(tuples[0]);
    size_t min_index = 0;

    if (extract_min_index(tuples, count, &min_index) == 0) {
        printf("Index of minimum value: %zu\n", min_index);
        printf("Minimum value: %d\n", tuples[min_index].value);
    } else {
        fprintf(stderr, "Error: Failed to extract minimum index\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}