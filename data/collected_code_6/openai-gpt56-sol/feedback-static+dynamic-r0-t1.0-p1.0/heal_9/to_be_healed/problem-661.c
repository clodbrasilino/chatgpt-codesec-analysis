#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <limits.h>
#include <errno.h>
#include <ctype.h>

static int read_line(char **buffer, size_t *capacity)
{
    size_t length = 0;

    if (buffer == NULL || capacity == NULL) {
        return 0;
    }

    if (*buffer == NULL || *capacity < 2) {
        char *new_buffer = malloc(128);

        if (new_buffer == NULL) {
            return 0;
        }

        free(*buffer);
        *buffer = new_buffer;
        *capacity = 128;
    }

    for (;;) {
        /* Possible weaknesses found:
         *  previous declaration of 'ch' with type 'int'
         *  Unused variable: ch [unusedVariable]
         *  previous definition is here
         */
        int ch;

        if (length >= *capacity - 1) {
            size_t new_capacity;
            char *new_buffer;

            if (*capacity > SIZE_MAX / 2) {
                if (length > SIZE_MAX - 2) {
                    return 0;
                }
                new_capacity = length + 2;
            } else {
                new_capacity = *capacity * 2;
            }

            if (new_capacity <= length + 1) {
                return 0;
            }

            new_buffer = realloc(*buffer, new_capacity);
            if (new_buffer == NULL) {
                return 0;
            }

            *buffer = new_buffer;
            *capacity = new_capacity;
        }

        /* Possible weaknesses found:
         *  redefinition of 'ch'
         *  redeclaration of 'ch' with no linkage
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int ch = fgetc(stdin);

        if (ch == EOF) {
            if (ferror(stdin) || length == 0) {
                return 0;
            }
            break;
        }

        if (ch == '\n') {
            if (length > 0 && (*buffer)[length - 1] == '\r') {
                --length;
            }
            break;
        }

        (*buffer)[length] = (char)ch;
        ++length;
    }

    (*buffer)[length] = '\0';
    return 1;
}

static int read_int64(int64_t *value)
{
    char *buffer = NULL;
    size_t capacity = 0;
    char *start;
    char *end;
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

    errno = 0;
    parsed = strtoimax(start, &end, 10);

    if (start != end &&
        errno != ERANGE &&
        parsed >= INT64_MIN &&
        parsed <= INT64_MAX) {
        while (isspace((unsigned char)*end)) {
            ++end;
        }

        if (*end == '\0') {
            *value = (int64_t)parsed;
            success = 1;
        }
    }

    free(buffer);
    return success;
}

static int read_size(size_t *value)
{
    char *buffer = NULL;
    size_t capacity = 0;
    char *start;
    char *end;
    int success = 0;

    if (value == NULL || !read_line(&buffer, &capacity)) {
        free(buffer);
        return 0;
    }

    start = buffer;
    while (isspace((unsigned char)*start)) {
        ++start;
    }

    if (*start != '-') {
        uintmax_t parsed;

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

static int add_checked(int64_t a, int64_t b, int64_t *result)
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
    int64_t skip = 0;
    int64_t take_one = 0;
    int64_t take_two = 0;
    int have_take_one = 0;
    int have_take_two = 0;
    size_t i;

    if (result == NULL || (values == NULL && count != 0)) {
        return 0;
    }

    for (i = 0; i < count; ++i) {
        int64_t next_skip = skip;
        int64_t next_take_one;
        int64_t next_take_two = 0;
        int next_have_take_two = 0;

        if (have_take_one && take_one > next_skip) {
            next_skip = take_one;
        }

        if (have_take_two && take_two > next_skip) {
            next_skip = take_two;
        }

        if (!add_checked(skip, values[i], &next_take_one)) {
            return 0;
        }

        if (have_take_one) {
            if (!add_checked(take_one, values[i], &next_take_two)) {
                return 0;
            }
            next_have_take_two = 1;
        }

        skip = next_skip;
        take_one = next_take_one;
        take_two = next_take_two;
        have_take_one = 1;
        have_take_two = next_have_take_two;
    }

    *result = skip;

    if (have_take_one && take_one > *result) {
        *result = take_one;
    }

    if (have_take_two && take_two > *result) {
        *result = take_two;
    }

    return 1;
}

int main(void)
{
    size_t count;
    int64_t *values = NULL;
    int64_t result;

    if (!read_size(&count)) {
        fprintf(stderr, "Failed to read the element count.\n");
        return EXIT_FAILURE;
    }

    if (count > SIZE_MAX / sizeof *values) {
        fprintf(stderr, "Element count is too large.\n");
        return EXIT_FAILURE;
    }

    if (count != 0) {
        values = malloc(count * sizeof *values);
        if (values == NULL) {
            fprintf(stderr, "Memory allocation failed.\n");
            return EXIT_FAILURE;
        }
    }

    for (size_t i = 0; i < count; ++i) {
        if (!read_int64(&values[i])) {
            fprintf(stderr, "Failed to read element %zu.\n", i);
            free(values);
            return EXIT_FAILURE;
        }
    }

    if (!max_sum_no_three_consecutive(values, count, &result)) {
        fprintf(stderr, "Unable to compute the result safely.\n");
        free(values);
        return EXIT_FAILURE;
    }

    if (printf("%" PRId64 "\n", result) < 0) {
        fprintf(stderr, "Failed to write the result.\n");
        free(values);
        return EXIT_FAILURE;
    }

    free(values);
    return EXIT_SUCCESS;
}