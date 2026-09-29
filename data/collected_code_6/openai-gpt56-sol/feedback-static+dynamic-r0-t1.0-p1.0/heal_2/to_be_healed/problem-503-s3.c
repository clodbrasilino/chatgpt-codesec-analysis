#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>
#include <ctype.h>

enum { MAX_LIST_SIZE = 1000000, INPUT_BUFFER_SIZE = 256 };

static int read_int64(int64_t *value)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[INPUT_BUFFER_SIZE];

    if (value == NULL || fgets(buffer, sizeof buffer, stdin) == NULL) {
        return 0;
    }

    char *start = buffer;
    while (isspace((unsigned char)*start)) {
        ++start;
    }

    errno = 0;
    char *end = NULL;
    intmax_t parsed = strtoimax(start, &end, 10);

    if (start == end || errno == ERANGE || parsed < INT64_MIN || parsed > INT64_MAX) {
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
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[INPUT_BUFFER_SIZE];

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

    errno = 0;
    char *end = NULL;
    uintmax_t parsed = strtoumax(start, &end, 10);

    if (start == end || errno == ERANGE || parsed > SIZE_MAX) {
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

static int add_consecutive_numbers(const int64_t *list, size_t length,
                                   int64_t *result)
{
    if ((list == NULL && length != 0U) || result == NULL) {
        return 0;
    }

    int64_t sum = 0;

    for (size_t i = 0U; i < length; ++i) {
        if ((list[i] > 0 && sum > INT64_MAX - list[i]) ||
            (list[i] < 0 && sum < INT64_MIN - list[i])) {
            return 0;
        }

        sum += list[i];
    }

    *result = sum;
    return 1;
}

int main(void)
{
    size_t length = 0U;

    if (!read_size(&length) || length > MAX_LIST_SIZE) {
        fputs("Invalid list length\n", stderr);
        return EXIT_FAILURE;
    }

    int64_t *list = NULL;

    if (length != 0U) {
        if (length > SIZE_MAX / sizeof *list) {
            fputs("List is too large\n", stderr);
            return EXIT_FAILURE;
        }

        list = malloc(length * sizeof *list);
        if (list == NULL) {
            fputs("Memory allocation failed\n", stderr);
            return EXIT_FAILURE;
        }
    }

    for (size_t i = 0U; i < length; ++i) {
        if (!read_int64(&list[i])) {
            fputs("Invalid list element\n", stderr);
            free(list);
            return EXIT_FAILURE;
        }
    }

    int64_t sum = 0;

    if (!add_consecutive_numbers(list, length, &sum)) {
        fputs("Arithmetic overflow\n", stderr);
        free(list);
        return EXIT_FAILURE;
    }

    if (printf("%" PRId64 "\n", sum) < 0) {
        fputs("Output error\n", stderr);
        free(list);
        return EXIT_FAILURE;
    }

    free(list);
    return EXIT_SUCCESS;
}