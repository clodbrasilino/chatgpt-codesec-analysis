#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int xor_tuples(const uint32_t *tuples, size_t tuple_count,
                      size_t tuple_size, uint32_t *result)
{
    size_t i;
    size_t j;

    if (tuples == NULL || result == NULL || tuple_count == 0U ||
        tuple_size == 0U || tuple_count > SIZE_MAX / tuple_size) {
        return -1;
    }

    for (j = 0U; j < tuple_size; ++j) {
        result[j] = 0U;
    }

    for (i = 0U; i < tuple_count; ++i) {
        for (j = 0U; j < tuple_size; ++j) {
            result[j] ^= tuples[i * tuple_size + j];
        }
    }

    return 0;
}

int main(void)
{
    const uint32_t tuples[][3] = {
        {1U, 2U, 3U},
        {4U, 5U, 6U},
        {7U, 8U, 9U}
    };
    const size_t tuple_count = sizeof(tuples) / sizeof(tuples[0]);
    const size_t tuple_size = sizeof(tuples[0]) / sizeof(tuples[0][0]);
    uint32_t *result;
    size_t i;

    if (tuple_size > SIZE_MAX / sizeof(*result)) {
        return EXIT_FAILURE;
    }

    result = calloc(tuple_size, sizeof(*result));
    if (result == NULL) {
        return EXIT_FAILURE;
    }

    if (xor_tuples(&tuples[0][0], tuple_count, tuple_size, result) != 0) {
        free(result);
        return EXIT_FAILURE;
    }

    for (i = 0U; i < tuple_size; ++i) {
        if (printf("%" PRIu32 "%c", result[i],
                   i + 1U == tuple_size ? '\n' : ' ') < 0) {
            free(result);
            return EXIT_FAILURE;
        }
    }

    free(result);

    if (fflush(stdout) == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}