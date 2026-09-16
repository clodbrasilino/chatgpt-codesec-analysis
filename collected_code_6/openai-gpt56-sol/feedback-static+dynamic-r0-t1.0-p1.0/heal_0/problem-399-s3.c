#include <inttypes.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

static int xor_tuples(const uint64_t *tuples, size_t tuple_count,
                      size_t tuple_length, uint64_t *result)
{
    size_t i;
    size_t j;

    if (tuples == NULL || result == NULL || tuple_count == 0U ||
        tuple_length == 0U || tuple_count > SIZE_MAX / tuple_length) {
        return -1;
    }

    for (j = 0U; j < tuple_length; ++j) {
        result[j] = 0U;
    }

    for (i = 0U; i < tuple_count; ++i) {
        for (j = 0U; j < tuple_length; ++j) {
            result[j] ^= tuples[(i * tuple_length) + j];
        }
    }

    return 0;
}

int main(void)
{
    static const uint64_t tuples[][3] = {
        {1U, 2U, 3U},
        {4U, 5U, 6U},
        {7U, 8U, 9U}
    };
    uint64_t result[3];
    size_t i;
    int status;

    status = xor_tuples(&tuples[0][0],
                        sizeof(tuples) / sizeof(tuples[0]),
                        sizeof(tuples[0]) / sizeof(tuples[0][0]),
                        result);
    if (status != 0) {
        (void)fprintf(stderr, "Unable to compute tuple XOR.\n");
        return 1;
    }

    for (i = 0U; i < sizeof(result) / sizeof(result[0]); ++i) {
        if (printf("%" PRIu64 "%c",
                   result[i],
                   (i + 1U == sizeof(result) / sizeof(result[0])) ? '\n' : ' ') < 0) {
            return 1;
        }
    }

    return 0;
}