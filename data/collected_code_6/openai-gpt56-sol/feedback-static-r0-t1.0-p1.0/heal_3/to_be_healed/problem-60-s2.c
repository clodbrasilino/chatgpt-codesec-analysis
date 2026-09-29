#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <stddef.h>
#include <errno.h>
#include <ctype.h>

static int read_int64(int64_t *value)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[128];

    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return 0;
    }

    char *start = buffer;
    while (isspace((unsigned char)*start)) {
        ++start;
    }

    errno = 0;
    char *end;
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

static int read_header(size_t *length, int64_t *difference)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[256];

    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return 0;
    }

    char *start = buffer;
    while (isspace((unsigned char)*start)) {
        ++start;
    }

    errno = 0;
    char *end;
    uintmax_t parsed_length = strtoumax(start, &end, 10);

    if (start == end || errno == ERANGE || parsed_length > SIZE_MAX) {
        return 0;
    }

    start = end;
    while (isspace((unsigned char)*start)) {
        ++start;
    }

    errno = 0;
    intmax_t parsed_difference = strtoimax(start, &end, 10);

    if (start == end || errno == ERANGE ||
        parsed_difference < INT64_MIN || parsed_difference > INT64_MAX) {
        return 0;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        return 0;
    }

    *length = (size_t)parsed_length;
    *difference = (int64_t)parsed_difference;
    return 1;
}

static size_t max_subsequence_length(const int64_t *array, size_t length,
                                     int64_t difference)
{
    if (array == NULL || length == 0) {
        return 0;
    }

    size_t best = 0;

    for (size_t i = 0; i < length; ++i) {
        size_t current = 1;
        int64_t value = array[i];

        for (size_t j = i + 1; j < length; ++j) {
            int matched;

            if (difference > 0) {
                matched = value <= INT64_MAX - difference &&
                          array[j] == value + difference;
            } else if (difference < 0) {
                matched = value >= INT64_MIN - difference &&
                          array[j] == value + difference;
            } else {
                matched = array[j] == value;
            }

            if (matched) {
                value = array[j];
                ++current;
            }
        }

        if (current > best) {
            best = current;
        }
    }

    return best;
}

int main(void)
{
    size_t length;
    int64_t difference;

    if (!read_header(&length, &difference)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (length > SIZE_MAX / sizeof(int64_t)) {
        fputs("Input size is too large\n", stderr);
        return EXIT_FAILURE;
    }

    if (length == 0) {
        puts("0");
        return EXIT_SUCCESS;
    }

    int64_t *array = malloc(length * sizeof(*array));
    if (array == NULL) {
        fputs("Memory allocation failed\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < length; ++i) {
        if (!read_int64(&array[i])) {
            fputs("Invalid input\n", stderr);
            free(array);
            return EXIT_FAILURE;
        }
    }

    printf("%zu\n", max_subsequence_length(array, length, difference));

    free(array);
    return EXIT_SUCCESS;
}