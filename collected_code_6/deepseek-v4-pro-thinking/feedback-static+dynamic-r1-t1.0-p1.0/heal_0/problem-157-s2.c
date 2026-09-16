#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct {
    size_t count;
    int value;
} rle_pair_t;

int rle_encode(const int *values, size_t value_count, rle_pair_t **pairs, size_t *pair_count) {
    if (pairs == NULL || pair_count == NULL) {
        return -1;
    }
    *pairs = NULL;
    *pair_count = 0;
    if (value_count > 0 && values == NULL) {
        return -1;
    }
    if (value_count == 0) {
        return 0;
    }
    if (value_count > SIZE_MAX / sizeof(rle_pair_t)) {
        return -2;
    }
    rle_pair_t *result = malloc(value_count * sizeof(*result));
    if (result == NULL) {
        return -3;
    }
    size_t run_count = 0;
    size_t i = 0;
    while (i < value_count) {
        int current = values[i];
        size_t j = i + 1;
        while (j < value_count && values[j] == current) {
            ++j;
        }
        result[run_count].count = j - i;
        result[run_count].value = current;
        ++run_count;
        i = j;
    }
    if (run_count < value_count) {
        rle_pair_t *shrunk = realloc(result, run_count * sizeof(*result));
        if (shrunk != NULL) {
            result = shrunk;
        }
    }
    *pairs = result;
    *pair_count = run_count;
    return 0;
}

int main(void) {
    int values[] = {1, 1, 1, 2, 2, 3, 3, 3, 3};
    size_t value_count = sizeof(values) / sizeof(values[0]);
    rle_pair_t *pairs = NULL;
    size_t pair_count = 0;
    int status = rle_encode(values, value_count, &pairs, &pair_count);
    if (status != 0) {
        fprintf(stderr, "Error: %d\n", status);
        return EXIT_FAILURE;
    }
    for (size_t i = 0; i < pair_count; ++i) {
        printf("%zu:%d ", pairs[i].count, pairs[i].value);
    }
    printf("\n");
    free(pairs);
    return EXIT_SUCCESS;
}