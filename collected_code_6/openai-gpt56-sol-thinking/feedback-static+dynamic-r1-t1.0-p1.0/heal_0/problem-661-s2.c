#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static bool read_token(char *buffer, size_t capacity)
{
    int ch;
    size_t length = 0;
    bool too_long = false;

    if (buffer == NULL || capacity < 2) {
        return false;
    }

    do {
        ch = fgetc(stdin);
        if (ch == EOF) {
            return false;
        }
    } while (isspace((unsigned char)ch));

    while (ch != EOF && !isspace((unsigned char)ch)) {
        if (length + 1 < capacity) {
            buffer[length++] = (char)ch;
        } else {
            too_long = true;
        }
        ch = fgetc(stdin);
    }

    if (ferror(stdin) || too_long) {
        return false;
    }

    buffer[length] = '\0';
    return true;
}

static bool parse_size(const char *text, size_t *value)
{
    char *end;
    uintmax_t parsed;

    if (text == NULL || value == NULL || text[0] == '\0' || text[0] == '-') {
        return false;
    }

    errno = 0;
    parsed = strtoumax(text, &end, 10);

    if (errno == ERANGE || *end != '\0' || parsed > SIZE_MAX) {
        return false;
    }

    *value = (size_t)parsed;
    return true;
}

static bool parse_int64(const char *text, int64_t *value)
{
    char *end;
    intmax_t parsed;

    if (text == NULL || value == NULL || text[0] == '\0') {
        return false;
    }

    errno = 0;
    parsed = strtoimax(text, &end, 10);

    if (errno == ERANGE || *end != '\0' ||
        parsed < INT64_MIN || parsed > INT64_MAX) {
        return false;
    }

    *value = (int64_t)parsed;
    return true;
}

static int checked_add_int64(int64_t left, int64_t right, int64_t *result)
{
    if (right > 0 && left > INT64_MAX - right) {
        return 1;
    }

    if (right < 0 && left < INT64_MIN - right) {
        return -1;
    }

    *result = left + right;
    return 0;
}

bool max_sum_no_three_consecutive(const int64_t *values,
                                  size_t count,
                                  int64_t *result)
{
    int64_t ending_with_zero = 0;
    int64_t ending_with_one = 0;
    int64_t ending_with_two = 0;
    bool one_valid = false;
    bool two_valid = false;

    if (result == NULL || (count > 0 && values == NULL)) {
        return false;
    }

    for (size_t i = 0; i < count; ++i) {
        int64_t new_zero = ending_with_zero;
        int64_t new_one;
        int64_t new_two = 0;
        bool new_two_valid = false;
        int status;

        if (one_valid && ending_with_one > new_zero) {
            new_zero = ending_with_one;
        }

        if (two_valid && ending_with_two > new_zero) {
            new_zero = ending_with_two;
        }

        status = checked_add_int64(ending_with_zero, values[i], &new_one);
        if (status != 0) {
            return false;
        }

        if (one_valid) {
            status = checked_add_int64(ending_with_one, values[i], &new_two);
            if (status > 0) {
                return false;
            }
            new_two_valid = status == 0;
        }

        ending_with_zero = new_zero;
        ending_with_one = new_one;
        ending_with_two = new_two;
        one_valid = true;
        two_valid = new_two_valid;
    }

    *result = ending_with_zero;

    if (one_valid && ending_with_one > *result) {
        *result = ending_with_one;
    }

    if (two_valid && ending_with_two > *result) {
        *result = ending_with_two;
    }

    return true;
}

int main(void)
{
    char token[128];
    size_t count;
    int64_t *values = NULL;
    int64_t result;

    if (!read_token(token, sizeof(token)) || !parse_size(token, &count)) {
        fputs("Invalid element count\n", stderr);
        return EXIT_FAILURE;
    }

    if (count > SIZE_MAX / sizeof(*values)) {
        fputs("Element count is too large\n", stderr);
        return EXIT_FAILURE;
    }

    if (count > 0) {
        values = malloc(count * sizeof(*values));
        if (values == NULL) {
            fputs("Memory allocation failed\n", stderr);
            return EXIT_FAILURE;
        }
    }

    for (size_t i = 0; i < count; ++i) {
        if (!read_token(token, sizeof(token)) ||
            !parse_int64(token, &values[i])) {
            fputs("Invalid element\n", stderr);
            free(values);
            return EXIT_FAILURE;
        }
    }

    if (!max_sum_no_three_consecutive(values, count, &result)) {
        fputs("Unable to compute the result\n", stderr);
        free(values);
        return EXIT_FAILURE;
    }

    printf("%" PRId64 "\n", result);
    free(values);
    return EXIT_SUCCESS;
}