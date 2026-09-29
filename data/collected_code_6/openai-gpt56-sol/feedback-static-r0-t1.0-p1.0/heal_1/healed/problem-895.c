#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <ctype.h>
#include <errno.h>

static int read_int64(int64_t *value)
{
    char buffer[128];

    if (value == NULL || fgets(buffer, sizeof buffer, stdin) == NULL) {
        return 0;
    }

    char *end;
    errno = 0;
    intmax_t parsed = strtoimax(buffer, &end, 10);

    if (end == buffer || errno == ERANGE || parsed < INT64_MIN ||
        parsed > INT64_MAX) {
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

static int read_size(size_t *value)
{
    char buffer[128];

    if (value == NULL || fgets(buffer, sizeof buffer, stdin) == NULL) {
        return 0;
    }

    char *start = buffer;
    while (isspace((unsigned char)*start)) {
        ++start;
    }

    if (*start == '-') {
        return 0;
    }

    char *end;
    errno = 0;
    uintmax_t parsed = strtoumax(start, &end, 10);

    if (end == start || errno == ERANGE || parsed == 0 ||
        parsed > SIZE_MAX / sizeof(int64_t)) {
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

static int max_non_adjacent_sum(const int64_t *array, size_t length,
                                int64_t *result)
{
    if (array == NULL || result == NULL || length == 0) {
        return 0;
    }

    int64_t previous_two = 0;
    int64_t previous_one = array[0] > 0 ? array[0] : 0;

    for (size_t i = 1; i < length; ++i) {
        int64_t include;

        if (array[i] > 0 && previous_two > INT64_MAX - array[i]) {
            return 0;
        }

        include = previous_two + array[i];

        if (include > previous_one) {
            previous_two = previous_one;
            previous_one = include;
        } else {
            previous_two = previous_one;
        }
    }

    *result = previous_one;
    return 1;
}

int main(void)
{
    size_t length;

    if (!read_size(&length)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    int64_t *array = malloc(length * sizeof *array);
    if (array == NULL) {
        perror("malloc");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < length; ++i) {
        if (!read_int64(&array[i])) {
            fputs("Invalid input\n", stderr);
            free(array);
            return EXIT_FAILURE;
        }
    }

    int64_t result;

    if (!max_non_adjacent_sum(array, length, &result)) {
        fputs("Unable to calculate result\n", stderr);
        free(array);
        return EXIT_FAILURE;
    }

    free(array);

    if (printf("%" PRId64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}