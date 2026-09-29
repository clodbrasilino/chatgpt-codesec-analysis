#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int read_size(size_t *value)
{
    char buffer[128];
    char *end;
    uintmax_t parsed;

    if (value == NULL || fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return -1;
    }

    errno = 0;
    end = NULL;
    parsed = strtoumax(buffer, &end, 10);

    if (errno == ERANGE || end == buffer || parsed > SIZE_MAX) {
        return -1;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r') {
        ++end;
    }

    if (*end != '\n' && *end != '\0') {
        return -1;
    }

    *value = (size_t)parsed;
    return 0;
}

static int read_uint64(uint64_t *value)
{
    char buffer[128];
    char *end;
    uintmax_t parsed;

    if (value == NULL || fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return -1;
    }

    errno = 0;
    end = NULL;
    parsed = strtoumax(buffer, &end, 10);

    if (errno == ERANGE || end == buffer || parsed > UINT64_MAX) {
        return -1;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r') {
        ++end;
    }

    if (*end != '\n' && *end != '\0') {
        return -1;
    }

    *value = (uint64_t)parsed;
    return 0;
}

static int sum_pairwise_xor(const uint64_t *array, size_t length,
                            uint64_t *result)
{
    uint64_t sum = 0;

    if (result == NULL || (length != 0U && array == NULL)) {
        return -1;
    }

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
    size_t length;
    uint64_t *array = NULL;
    uint64_t result;

    if (read_size(&length) != 0 ||
        length > UINT64_MAX ||
        length > SIZE_MAX / sizeof(*array)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (length != 0U) {
        array = malloc(length * sizeof(*array));
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