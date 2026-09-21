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
        char *new_buffer;
        size_t new_capacity = 128;

        new_buffer = malloc(new_capacity);
        if (new_buffer == NULL) {
            return 0;
        }

        free(*buffer);
        *buffer = new_buffer;
        *capacity = new_capacity;
    }

    (*buffer)[0] = '\0';

    for (;;) {
        size_t available;
        char *destination;

        if (length >= *capacity) {
            return 0;
        }

        available = *capacity - length;
        destination = *buffer + length;

        if (available > (size_t)INT_MAX) {
            available = (size_t)INT_MAX;
        }

        if (fgets(destination, (int)available, stdin) == NULL) {
            return length != 0 && feof(stdin);
        }

        {
            size_t added = strnlen(destination, available);

            if (added == available) {
                return 0;
            }

            length += added;
        }

        if (length > 0 && (*buffer)[length - 1] == '\n') {
            (*buffer)[--length] = '\0';

            if (length > 0 && (*buffer)[length - 1] == '\r') {
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
        intmax_t parsed;

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

    if (result == NULL || (values == NULL && count != 0)) {
        return 0;
    }

    for (size_t i = 0; i < count; ++i) {
        int64_t current[3];

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

        previous[0] = current[0];
        previous[1] = current[1];
        previous[2] = current[2];
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