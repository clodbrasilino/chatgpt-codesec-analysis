#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int value;
    size_t count;
} ItemCount;

static int count_repeated_items(const int *tuple, size_t length,
                                ItemCount **results, size_t *result_count)
{
    ItemCount *counts;
    size_t unique_count = 0;

    if (results == NULL || result_count == NULL) {
        return -1;
    }

    *results = NULL;
    *result_count = 0;

    if (length == 0) {
        return 0;
    }

    if (tuple == NULL || length > SIZE_MAX / sizeof(*counts)) {
        return -1;
    }

    counts = calloc(length, sizeof(*counts));
    if (counts == NULL) {
        return -1;
    }

    for (size_t i = 0; i < length; ++i) {
        size_t j;

        for (j = 0; j < unique_count; ++j) {
            if (counts[j].value == tuple[i]) {
                ++counts[j].count;
                break;
            }
        }

        if (j == unique_count) {
            counts[unique_count].value = tuple[i];
            counts[unique_count].count = 1;
            ++unique_count;
        }
    }

    *results = counts;
    *result_count = unique_count;
    return 0;
}

int main(void)
{
    const int tuple[] = {1, 2, 3, 2, 1, 2, 4, 3, 3};
    const size_t length = sizeof(tuple) / sizeof(tuple[0]);
    ItemCount *counts = NULL;
    size_t count_length = 0;

    if (count_repeated_items(tuple, length, &counts, &count_length) != 0) {
        fputs("Unable to count tuple items.\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < count_length; ++i) {
        if (printf("%d: %zu\n", counts[i].value, counts[i].count) < 0) {
            free(counts);
            return EXIT_FAILURE;
        }
    }

    free(counts);
    return EXIT_SUCCESS;
}