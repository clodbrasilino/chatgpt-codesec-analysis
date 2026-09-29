#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int read_uint64(uint64_t *value)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[128];
    char *end;

    if (value == NULL || fgets(buffer, sizeof buffer, stdin) == NULL) {
        return -1;
    }

    errno = 0;
    uintmax_t parsed = strtoumax(buffer, &end, 10);

    if (end == buffer || errno == ERANGE || parsed > UINT64_MAX) {
        return -1;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r' || *end == '\n') {
        ++end;
    }

    if (*end != '\0') {
        return -1;
    }

    *value = (uint64_t)parsed;
    return 0;
}

static int sum_pairwise_xor(const uint64_t *array, size_t length,
                            uint64_t *result)
{
    if (result == NULL || (length != 0U && array == NULL)) {
        return -1;
    }

    uint64_t sum = 0;

    for (unsigned int bit = 0; bit < 64U; ++bit) {
        uint64_t ones = 0;

        for (size_t i = 0; i < length; ++i) {
            ones += (array[i] >> bit) & UINT64_C(1);
        }

        uint64_t zeros = (uint64_t)length - ones;

        if (ones != 0U && zeros > UINT64_MAX / ones) {
            return -1;
        }

        uint64_t pairs = ones * zeros;

        if (pairs > (UINT64_MAX >> bit)) {
            return -1;
        }

        uint64_t contribution = pairs << bit;

        if (contribution > UINT64_MAX - sum) {
            return -1;
        }

        sum += contribution;
    }

    *result = sum;
    return 0;
}

int main(void)
{
    uint64_t input_length;

    if (read_uint64(&input_length) != 0 ||
        input_length > SIZE_MAX ||
        input_length > SIZE_MAX / sizeof(uint64_t)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    size_t length = (size_t)input_length;
    uint64_t *array = NULL;

    if (length != 0U) {
        array = malloc(length * sizeof *array);
        if (array == NULL) {
            fputs("Allocation failed\n", stderr);
            return EXIT_FAILURE;
        }
    }

    for (size_t i = 0; i < length; ++i) {
        if (read_uint64(&array[i]) != 0) {
            fputs("Invalid input\n", stderr);
            free(array);
            return EXIT_FAILURE;
        }
    }

    uint64_t result;

    if (sum_pairwise_xor(array, length, &result) != 0) {
        fputs("Result overflow\n", stderr);
        free(array);
        return EXIT_FAILURE;
    }

    free(array);

    if (printf("%" PRIu64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}