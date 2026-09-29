#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>
#include <ctype.h>

static int read_int64(int64_t *value)
{
    char buffer[256];
    char *start;
    char *end;

    if (value == NULL || fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return -1;
    }

    start = buffer;
    while (isspace((unsigned char)*start)) {
        ++start;
    }

    errno = 0;
    intmax_t parsed = strtoimax(start, &end, 10);

    if (start == end || errno == ERANGE || parsed < INT64_MIN ||
        parsed > INT64_MAX) {
        return -1;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        return -1;
    }

    *value = (int64_t)parsed;
    return 0;
}

static int read_size(size_t *value)
{
    char buffer[256];
    char *start;
    char *end;

    if (value == NULL || fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return -1;
    }

    start = buffer;
    while (isspace((unsigned char)*start)) {
        ++start;
    }

    if (*start == '-') {
        return -1;
    }

    errno = 0;
    uintmax_t parsed = strtoumax(start, &end, 10);

    if (start == end || errno == ERANGE || parsed == 0 ||
        parsed > SIZE_MAX) {
        return -1;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        return -1;
    }

    *value = (size_t)parsed;
    return 0;
}

static int find_max_sum_increasing_subsequence(const int64_t *array,
                                               size_t length,
                                               int64_t *result)
{
    int64_t *sums;
    int64_t maximum;

    if (array == NULL || result == NULL || length == 0) {
        return -1;
    }

    if (length > SIZE_MAX / sizeof(*sums)) {
        return -1;
    }

    sums = malloc(length * sizeof(*sums));
    if (sums == NULL) {
        return -1;
    }

    maximum = array[0];

    for (size_t i = 0; i < length; ++i) {
        sums[i] = array[i];

        for (size_t j = 0; j < i; ++j) {
            if (array[j] < array[i]) {
                if ((array[i] > 0 && sums[j] > INT64_MAX - array[i]) ||
                    (array[i] < 0 && sums[j] < INT64_MIN - array[i])) {
                    free(sums);
                    return -1;
                }

                int64_t candidate = sums[j] + array[i];

                if (candidate > sums[i]) {
                    sums[i] = candidate;
                }
            }
        }

        if (sums[i] > maximum) {
            maximum = sums[i];
        }
    }

    free(sums);
    *result = maximum;
    return 0;
}

int main(void)
{
    size_t length;
    int64_t *array;
    int64_t result;

    if (read_size(&length) != 0) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (length > SIZE_MAX / sizeof(*array)) {
        fputs("Input is too large\n", stderr);
        return EXIT_FAILURE;
    }

    array = malloc(length * sizeof(*array));
    if (array == NULL) {
        fputs("Memory allocation failed\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < length; ++i) {
        if (read_int64(&array[i]) != 0) {
            fputs("Invalid input\n", stderr);
            free(array);
            return EXIT_FAILURE;
        }
    }

    if (find_max_sum_increasing_subsequence(array, length, &result) != 0) {
        fputs("Unable to calculate result\n", stderr);
        free(array);
        return EXIT_FAILURE;
    }

    printf("%" PRId64 "\n", result);
    free(array);
    return EXIT_SUCCESS;
}