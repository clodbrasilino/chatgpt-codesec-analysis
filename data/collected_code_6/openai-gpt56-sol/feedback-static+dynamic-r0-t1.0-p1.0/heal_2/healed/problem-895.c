#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <limits.h>
#include <errno.h>
#include <ctype.h>
#include <string.h>

static int read_int64(int64_t *value)
{
    char buffer[256];

    if (value == NULL || fgets(buffer, sizeof buffer, stdin) == NULL) {
        return 0;
    }

    if (strchr(buffer, '\n') == NULL && !feof(stdin)) {
        int ch;

        do {
            ch = getchar();
        } while (ch != '\n' && ch != EOF);

        return 0;
    }

    char *start = buffer;

    while (isspace((unsigned char)*start)) {
        ++start;
    }

    errno = 0;

    char *end = NULL;
    intmax_t parsed = strtoimax(start, &end, 10);

    if (start == end || errno == ERANGE ||
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

static int read_size(size_t *value)
{
    int64_t parsed;

    if (value == NULL || !read_int64(&parsed) || parsed <= 0) {
        return 0;
    }

    if ((uintmax_t)parsed > SIZE_MAX) {
        return 0;
    }

    *value = (size_t)parsed;
    return 1;
}

static int checked_add_int64(int64_t left, int64_t right, int64_t *result)
{
    if (result == NULL) {
        return 0;
    }

    if ((right > 0 && left > INT64_MAX - right) ||
        (right < 0 && left < INT64_MIN - right)) {
        return 0;
    }

    *result = left + right;
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

        if (!checked_add_int64(previous_two, array[i], &include)) {
            return 0;
        }

        int64_t current = previous_one > include ? previous_one : include;
        previous_two = previous_one;
        previous_one = current;
    }

    *result = previous_one;
    return 1;
}

int main(void)
{
    size_t length;

    if (!read_size(&length) || length > SIZE_MAX / sizeof(int64_t)) {
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

    if (printf("%" PRId64 "\n", result) < 0) {
        free(array);
        return EXIT_FAILURE;
    }

    free(array);
    return EXIT_SUCCESS;
}