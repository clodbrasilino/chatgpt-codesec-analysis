#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>
#include <ctype.h>

static int read_int64(int64_t *value)
{
    char buffer[128];
    char *start;
    char *end;

    if (value == NULL || fgets(buffer, sizeof buffer, stdin) == NULL) {
        return -1;
    }

    start = buffer;
    while (isspace((unsigned char)*start)) {
        ++start;
    }

    errno = 0;
    intmax_t parsed = strtoimax(start, &end, 10);

    if (start == end || errno == ERANGE ||
        parsed < INT64_MIN || parsed > INT64_MAX) {
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

static int minimum_number_to_make_sum_even(
    const int64_t array[],
    size_t length,
    int64_t *result)
{
    int parity = 0;

    if (result == NULL || (array == NULL && length != 0U)) {
        return -1;
    }

    for (size_t i = 0U; i < length; ++i) {
        parity ^= (int)((uint64_t)array[i] & UINT64_C(1));
    }

    *result = (int64_t)parity;
    return 0;
}

int main(void)
{
    int64_t input_length;
    size_t length;
    int64_t *array = NULL;
    int64_t minimum = 0;

    if (read_int64(&input_length) != 0 || input_length < 0) {
        fputs("Invalid array length.\n", stderr);
        return EXIT_FAILURE;
    }

    if ((uintmax_t)input_length > SIZE_MAX) {
        fputs("Array is too large.\n", stderr);
        return EXIT_FAILURE;
    }

    length = (size_t)input_length;

    if (length > SIZE_MAX / sizeof *array) {
        fputs("Array is too large.\n", stderr);
        return EXIT_FAILURE;
    }

    if (length != 0U) {
        array = malloc(length * sizeof *array);
        if (array == NULL) {
            fputs("Memory allocation failed.\n", stderr);
            return EXIT_FAILURE;
        }
    }

    for (size_t i = 0U; i < length; ++i) {
        if (read_int64(&array[i]) != 0) {
            fputs("Invalid array element.\n", stderr);
            free(array);
            return EXIT_FAILURE;
        }
    }

    if (minimum_number_to_make_sum_even(array, length, &minimum) != 0) {
        fputs("Unable to compute the result.\n", stderr);
        free(array);
        return EXIT_FAILURE;
    }

    printf("%" PRId64 "\n", minimum);
    free(array);

    return EXIT_SUCCESS;
}