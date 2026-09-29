#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>

static int minimum_to_make_sum_even(const int64_t *array, size_t length, int64_t *result)
{
    if ((array == NULL && length != 0U) || result == NULL) {
        return 0;
    }

    unsigned int parity = 0U;

    for (size_t i = 0; i < length; ++i) {
        parity ^= (unsigned int)((uint64_t)array[i] & UINT64_C(1));
    }

    *result = (int64_t)parity;
    return 1;
}

static int read_size(size_t *value)
{
    char buffer[128];
    char *end;
    uintmax_t parsed;

    if (value == NULL || fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return 0;
    }

    errno = 0;
    parsed = strtoumax(buffer, &end, 10);

    if (end == buffer || errno == ERANGE || parsed > SIZE_MAX) {
        return 0;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r') {
        ++end;
    }

    if (*end != '\n' && *end != '\0') {
        return 0;
    }

    *value = (size_t)parsed;
    return 1;
}

static int read_int64(int64_t *value)
{
    char buffer[128];
    char *end;
    intmax_t parsed;

    if (value == NULL || fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return 0;
    }

    errno = 0;
    parsed = strtoimax(buffer, &end, 10);

    if (end == buffer || errno == ERANGE ||
        parsed < INT64_MIN || parsed > INT64_MAX) {
        return 0;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r') {
        ++end;
    }

    if (*end != '\n' && *end != '\0') {
        return 0;
    }

    *value = (int64_t)parsed;
    return 1;
}

int main(void)
{
    size_t length;
    int64_t *array = NULL;
    int64_t minimum;

    if (!read_size(&length)) {
        return EXIT_FAILURE;
    }

    if (length > SIZE_MAX / sizeof(*array)) {
        return EXIT_FAILURE;
    }

    if (length != 0U) {
        array = malloc(length * sizeof(*array));
        if (array == NULL) {
            return EXIT_FAILURE;
        }

        for (size_t i = 0; i < length; ++i) {
            if (!read_int64(&array[i])) {
                free(array);
                return EXIT_FAILURE;
            }
        }
    }

    if (!minimum_to_make_sum_even(array, length, &minimum)) {
        free(array);
        return EXIT_FAILURE;
    }

    if (printf("%" PRId64 "\n", minimum) < 0) {
        free(array);
        return EXIT_FAILURE;
    }

    free(array);
    return EXIT_SUCCESS;
}