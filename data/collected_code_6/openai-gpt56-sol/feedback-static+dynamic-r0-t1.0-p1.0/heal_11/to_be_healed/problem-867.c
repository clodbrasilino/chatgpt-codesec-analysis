#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>
#include <ctype.h>
#include <limits.h>

#define MAX_LINE_LENGTH 4096U

static int discard_line(void)
{
    int ch;

    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = getchar()) != '\n') {
        if (ch == EOF) {
            return feof(stdin) ? 1 : 0;
        }
    }

    return 1;
}

static int read_line(char *buffer, size_t capacity)
{
    if (buffer == NULL || capacity < 2U || capacity > (size_t)INT_MAX) {
        return 0;
    }

    if (fgets(buffer, (int)capacity, stdin) == NULL) {
        return 0;
    }

    size_t length = 0U;

    while (buffer[length] != '\0' && buffer[length] != '\n') {
        ++length;
    }

    if (buffer[length] == '\n') {
        buffer[length] = '\0';
        return 1;
    }

    if (feof(stdin)) {
        return 1;
    }

    discard_line();
    return 0;
}

static char *skip_space(char *text)
{
    while (isspace((unsigned char)*text)) {
        ++text;
    }

    return text;
}

static int only_trailing_space(char *text)
{
    return *skip_space(text) == '\0';
}

static int read_size(size_t *value)
{
    if (value == NULL) {
        return 0;
    }

    char *buffer = malloc(MAX_LINE_LENGTH);

    if (buffer == NULL) {
        return 0;
    }

    if (!read_line(buffer, MAX_LINE_LENGTH)) {
        free(buffer);
        return 0;
    }

    char *start = skip_space(buffer);

    if (*start == '\0' || *start == '-') {
        free(buffer);
        return 0;
    }

    errno = 0;
    char *end = NULL;
    uintmax_t parsed = strtoumax(start, &end, 10);

    if (errno == ERANGE || end == start ||
        parsed > (uintmax_t)SIZE_MAX || !only_trailing_space(end)) {
        free(buffer);
        return 0;
    }

    *value = (size_t)parsed;
    free(buffer);
    return 1;
}

static int read_int64(int64_t *value)
{
    if (value == NULL) {
        return 0;
    }

    char *buffer = malloc(MAX_LINE_LENGTH);

    if (buffer == NULL) {
        return 0;
    }

    if (!read_line(buffer, MAX_LINE_LENGTH)) {
        free(buffer);
        return 0;
    }

    char *start = skip_space(buffer);

    if (*start == '\0') {
        free(buffer);
        return 0;
    }

    errno = 0;
    char *end = NULL;
    intmax_t parsed = strtoimax(start, &end, 10);

    if (errno == ERANGE || end == start ||
        parsed < INT64_MIN || parsed > INT64_MAX ||
        !only_trailing_space(end)) {
        free(buffer);
        return 0;
    }

    *value = (int64_t)parsed;
    free(buffer);
    return 1;
}

static int minimum_to_make_sum_even(const int64_t *array, size_t length,
                                    int64_t *result)
{
    if (result == NULL || (array == NULL && length != 0U)) {
        return 0;
    }

    uint64_t parity = 0U;

    for (size_t i = 0U; i < length; ++i) {
        parity ^= (uint64_t)array[i] & UINT64_C(1);
    }

    *result = (int64_t)parity;
    return 1;
}

int main(void)
{
    size_t length;

    if (!read_size(&length) || length > SIZE_MAX / sizeof(int64_t)) {
        return EXIT_FAILURE;
    }

    int64_t *array = NULL;

    if (length != 0U) {
        array = malloc(length * sizeof *array);

        if (array == NULL) {
            return EXIT_FAILURE;
        }

        for (size_t i = 0U; i < length; ++i) {
            if (!read_int64(&array[i])) {
                free(array);
                return EXIT_FAILURE;
            }
        }
    }

    int64_t minimum;

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