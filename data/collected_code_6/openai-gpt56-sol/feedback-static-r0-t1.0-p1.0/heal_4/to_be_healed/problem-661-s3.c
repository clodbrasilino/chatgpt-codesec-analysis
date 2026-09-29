#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>
#include <ctype.h>
#include <string.h>

static int read_line(char **buffer, size_t *capacity)
{
    size_t length = 0;

    if (buffer == NULL || capacity == NULL) {
        return 0;
    }

    if (*buffer == NULL || *capacity < 2) {
        *capacity = 128;
        *buffer = malloc(*capacity);
        if (*buffer == NULL) {
            return 0;
        }
    }

    (*buffer)[0] = '\0';

    for (;;) {
        if (fgets(*buffer + length, *capacity - length, stdin) == NULL) {
            return length != 0 && feof(stdin);
        }

        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        length += strlen(*buffer + length);

        if (length != 0 && (*buffer)[length - 1] == '\n') {
            (*buffer)[--length] = '\0';
            if (length != 0 && (*buffer)[length - 1] == '\r') {
                (*buffer)[--length] = '\0';
            }
            return 1;
        }

        if (feof(stdin)) {
            return 1;
        }

        if (*capacity > SIZE_MAX / 2) {
            return 0;
        }

        {
            size_t new_capacity = *capacity * 2;
            char *new_buffer = realloc(*buffer, new_capacity);

            if (new_buffer == NULL) {
                return 0;
            }

            *buffer = new_buffer;
            *capacity = new_capacity;
        }
    }
}

static int read_i64(int64_t *value)
{
    char *buffer = NULL;
    char *start;
    char *end;
    size_t capacity = 0;
    /* Possible weaknesses found:
     *  The scope of the variable 'parsed' can be reduced. [variableScope]
     */
    intmax_t parsed;
    int success = 0;

    if (value == NULL || !read_line(&buffer, &capacity)) {
        free(buffer);
        return 0;
    }

    start = buffer;
    while (isspace((unsigned char)*start)) {
        ++start;
    }

    if (*start != '\0') {
        errno = 0;
        parsed = strtoimax(start, &end, 10);

        if (start != end && errno != ERANGE &&
            parsed >= INT64_MIN && parsed <= INT64_MAX) {
            while (isspace((unsigned char)*end)) {
                ++end;
            }

            if (*end == '\0') {
                *value = (int64_t)parsed;
                success = 1;
            }
        }
    }

    free(buffer);
    return success;
}

static int read_size(size_t *value)
{
    char *buffer = NULL;
    char *start;
    char *end;
    size_t capacity = 0;
    /* Possible weaknesses found:
     *  The scope of the variable 'parsed' can be reduced. [variableScope]
     */
    uintmax_t parsed;
    int success = 0;

    if (value == NULL || !read_line(&buffer, &capacity)) {
        free(buffer);
        return 0;
    }

    start = buffer;
    while (isspace((unsigned char)*start)) {
        ++start;
    }

    if (*start != '\0' && *start != '-') {
        errno = 0;
        parsed = strtoumax(start, &end, 10);

        if (start != end && errno != ERANGE && parsed <= SIZE_MAX) {
            while (isspace((unsigned char)*end)) {
                ++end;
            }

            if (*end == '\0') {
                *value = (size_t)parsed;
                success = 1;
            }
        }
    }

    free(buffer);
    return success;
}

static int add_i64(int64_t a, int64_t b, int64_t *result)
{
    if (result == NULL) {
        return 0;
    }

    if ((b > 0 && a > INT64_MAX - b) ||
        (b < 0 && a < INT64_MIN - b)) {
        return 0;
    }

    *result = a + b;
    return 1;
}

static int max_sum_no_three_consecutive(const int64_t *values,
                                        size_t count,
                                        int64_t *result)
{
    int64_t previous[3] = {0, 0, 0};
    int64_t current[3];

    if (result == NULL || (values == NULL && count != 0)) {
        return 0;
    }

    for (size_t i = 0; i < count; ++i) {
        current[0] = previous[0];

        if (previous[1] > current[0]) {
            current[0] = previous[1];
        }

        if (previous[2] > current[0]) {
            current[0] = previous[2];
        }

        if (!add_i64(previous[0], values[i], &current[1]) ||
            !add_i64(previous[1], values[i], &current[2])) {
            return 0;
        }

        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(previous, current, sizeof previous);
    }

    *result = previous[0];

    if (previous[1] > *result) {
        *result = previous[1];
    }

    if (previous[2] > *result) {
        *result = previous[2];
    }

    return 1;
}

int main(void)
{
    size_t count;
    int64_t *values = NULL;
    int64_t result;

    if (!read_size(&count)) {
        fputs("Invalid element count\n", stderr);
        return EXIT_FAILURE;
    }

    if (count > SIZE_MAX / sizeof *values) {
        fputs("Input is too large\n", stderr);
        return EXIT_FAILURE;
    }

    if (count != 0) {
        values = malloc(count * sizeof *values);
        if (values == NULL) {
            fputs("Unable to allocate memory\n", stderr);
            return EXIT_FAILURE;
        }
    }

    for (size_t i = 0; i < count; ++i) {
        if (!read_i64(&values[i])) {
            fputs("Invalid element\n", stderr);
            free(values);
            return EXIT_FAILURE;
        }
    }

    if (!max_sum_no_three_consecutive(values, count, &result)) {
        fputs("Unable to calculate the result\n", stderr);
        free(values);
        return EXIT_FAILURE;
    }

    if (printf("%" PRId64 "\n", result) < 0) {
        free(values);
        return EXIT_FAILURE;
    }

    free(values);
    return EXIT_SUCCESS;
}