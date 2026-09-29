#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <limits.h>
#include <errno.h>
#include <ctype.h>

static int read_size(size_t *value)
{
    char buffer[128];

    if (fgets(buffer, sizeof buffer, stdin) == NULL) {
        return 0;
    }

    char *end;
    errno = 0;
    uintmax_t parsed = strtoumax(buffer, &end, 10);

    if (errno == ERANGE || end == buffer || parsed > SIZE_MAX) {
        return 0;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        return 0;
    }

    *value = (size_t)parsed;
    return 1;
}

static int read_int64(int64_t *value)
{
    char buffer[128];

    if (fgets(buffer, sizeof buffer, stdin) == NULL) {
        return 0;
    }

    char *end;
    errno = 0;
    intmax_t parsed = strtoimax(buffer, &end, 10);

    if (errno == ERANGE || end == buffer ||
        parsed < INT64_MIN || parsed > INT64_MAX) {
        return 0;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        return 0;
    }

    *value = (int64_t)parsed;
    return 1;
}

static int add_overflows_int64(int64_t a, int64_t b)
{
    return (b > 0 && a > INT64_MAX - b) ||
           (b < 0 && a < INT64_MIN - b);
}

static size_t max_sum_subarray_length(const int64_t *array, size_t length)
{
    if (array == NULL || length == 0) {
        return 0;
    }

    int64_t current_sum = array[0];
    int64_t maximum_sum = array[0];
    size_t current_start = 0;
    size_t best_length = 1;

    for (size_t i = 1; i < length; ++i) {
        if (current_sum < 0 ||
            add_overflows_int64(current_sum, array[i])) {
            current_sum = array[i];
            current_start = i;
        } else {
            current_sum += array[i];
        }

        size_t current_length = i - current_start + 1;

        if (current_sum > maximum_sum ||
            (current_sum == maximum_sum &&
             current_length > best_length)) {
            maximum_sum = current_sum;
            best_length = current_length;
        }
    }

    return best_length;
}

int main(void)
{
    size_t length;

    if (!read_size(&length) ||
        length == 0 ||
        length > SIZE_MAX / sizeof(int64_t)) {
        return EXIT_FAILURE;
    }

    int64_t *array = malloc(length * sizeof *array);
    if (array == NULL) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < length; ++i) {
        if (!read_int64(&array[i])) {
            free(array);
            return EXIT_FAILURE;
        }
    }

    size_t result = max_sum_subarray_length(array, length);
    free(array);

    if (printf("%zu\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}