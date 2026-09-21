#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>
#include <ctype.h>

#define MAX_INPUT_LINE_LENGTH 4096U

static int discard_line_remainder(void)
{
    char discard[256];

    for (;;) {
        size_t i;

        if (fgets(discard, (int)sizeof(discard), stdin) == NULL) {
            return ferror(stdin) ? -1 : 0;
        }

        for (i = 0; discard[i] != '\0'; ++i) {
            if (discard[i] == '\n') {
                return 0;
            }
        }
    }
}

static int read_line(char **line)
{
    char *buffer;
    size_t length;

    if (line == NULL || MAX_INPUT_LINE_LENGTH >= (size_t)INT_MAX) {
        return -1;
    }

    *line = NULL;

    buffer = malloc(MAX_INPUT_LINE_LENGTH + 1U);
    if (buffer == NULL) {
        return -1;
    }

    if (fgets(buffer, (int)(MAX_INPUT_LINE_LENGTH + 1U), stdin) == NULL) {
        free(buffer);
        return -1;
    }

    length = 0;
    while (buffer[length] != '\0' && buffer[length] != '\n') {
        ++length;
    }

    if (buffer[length] == '\n') {
        buffer[length] = '\0';
    } else if (length == MAX_INPUT_LINE_LENGTH) {
        if (discard_line_remainder() != 0) {
            free(buffer);
            return -1;
        }

        free(buffer);
        return -1;
    }

    *line = buffer;
    return 0;
}

static int read_int64(int64_t *value)
{
    char *buffer;
    char *start;
    char *end;
    intmax_t parsed;

    if (value == NULL || read_line(&buffer) != 0) {
        return -1;
    }

    start = buffer;
    while (isspace((unsigned char)*start) != 0) {
        ++start;
    }

    errno = 0;
    parsed = strtoimax(start, &end, 10);

    if (start == end || errno == ERANGE ||
        parsed < (intmax_t)INT64_MIN || parsed > (intmax_t)INT64_MAX) {
        free(buffer);
        return -1;
    }

    while (isspace((unsigned char)*end) != 0) {
        ++end;
    }

    if (*end != '\0') {
        free(buffer);
        return -1;
    }

    *value = (int64_t)parsed;
    free(buffer);
    return 0;
}

static int read_size(size_t *value)
{
    char *buffer;
    char *start;
    char *end;
    uintmax_t parsed;

    if (value == NULL || read_line(&buffer) != 0) {
        return -1;
    }

    start = buffer;
    while (isspace((unsigned char)*start) != 0) {
        ++start;
    }

    if (*start == '-') {
        free(buffer);
        return -1;
    }

    errno = 0;
    parsed = strtoumax(start, &end, 10);

    if (start == end || errno == ERANGE || parsed == 0 ||
        parsed > (uintmax_t)SIZE_MAX) {
        free(buffer);
        return -1;
    }

    while (isspace((unsigned char)*end) != 0) {
        ++end;
    }

    if (*end != '\0') {
        free(buffer);
        return -1;
    }

    *value = (size_t)parsed;
    free(buffer);
    return 0;
}

static int checked_add_int64(int64_t left, int64_t right, int64_t *result)
{
    if (result == NULL) {
        return -1;
    }

    if ((right > 0 && left > INT64_MAX - right) ||
        (right < 0 && left < INT64_MIN - right)) {
        return -1;
    }

    *result = left + right;
    return 0;
}

static int find_max_sum_increasing_subsequence(const int64_t *array,
                                                size_t length,
                                                int64_t *result)
{
    int64_t *sums;
    int64_t maximum;
    size_t i;

    if (array == NULL || result == NULL || length == 0 ||
        length > SIZE_MAX / sizeof(*sums)) {
        return -1;
    }

    sums = malloc(length * sizeof(*sums));
    if (sums == NULL) {
        return -1;
    }

    maximum = array[0];

    for (i = 0; i < length; ++i) {
        size_t j;

        sums[i] = array[i];

        for (j = 0; j < i; ++j) {
            int64_t candidate;

            if (array[j] >= array[i] ||
                checked_add_int64(sums[j], array[i], &candidate) != 0) {
                continue;
            }

            if (candidate > sums[i]) {
                sums[i] = candidate;
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
    size_t i;
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

    for (i = 0; i < length; ++i) {
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

    if (printf("%" PRId64 "\n", result) < 0) {
        free(array);
        return EXIT_FAILURE;
    }

    free(array);
    return EXIT_SUCCESS;
}