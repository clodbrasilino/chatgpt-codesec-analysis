#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct {
    size_t count;
    int value;
} Run;

int decode_rle(const Run *runs, size_t run_count, int **decoded, size_t *decoded_count)
{
    size_t total = 0;
    size_t position = 0;
    int *result = NULL;

    if (decoded == NULL || decoded_count == NULL ||
        (runs == NULL && run_count != 0)) {
        return -1;
    }

    *decoded = NULL;
    *decoded_count = 0;

    for (size_t i = 0; i < run_count; ++i) {
        if (runs[i].count > SIZE_MAX - total) {
            return -1;
        }
        total += runs[i].count;
    }

    if (total == 0) {
        return 0;
    }

    if (total > SIZE_MAX / sizeof(*result)) {
        return -1;
    }

    result = malloc(total * sizeof(*result));
    if (result == NULL) {
        return -1;
    }

    for (size_t i = 0; i < run_count; ++i) {
        for (size_t j = 0; j < runs[i].count; ++j) {
            result[position++] = runs[i].value;
        }
    }

    *decoded = result;
    *decoded_count = total;
    return 0;
}

int main(void)
{
    const Run encoded[] = {
        {3, 1},
        {2, 4},
        {1, 7},
        {4, 9}
    };
    const size_t run_count = sizeof(encoded) / sizeof(encoded[0]);
    int *decoded = NULL;
    size_t decoded_count = 0;

    if (decode_rle(encoded, run_count, &decoded, &decoded_count) != 0) {
        fputs("Failed to decode the list.\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < decoded_count; ++i) {
        if (printf("%s%d", i == 0 ? "" : " ", decoded[i]) < 0) {
            free(decoded);
            return EXIT_FAILURE;
        }
    }

    if (putchar('\n') == EOF) {
        free(decoded);
        return EXIT_FAILURE;
    }

    free(decoded);
    return EXIT_SUCCESS;
}