#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <stddef.h>
#include <errno.h>
#include <ctype.h>
#include <limits.h>

static int compare_ints(const void *lhs, const void *rhs)
{
    const int a = *(const int *)lhs;
    const int b = *(const int *)rhs;

    return (a > b) - (a < b);
}

static uint64_t count_pairs(int *values, size_t count, int64_t target)
{
    size_t left = 0U;
    size_t right;
    uint64_t pairs = 0U;

    if (values == NULL || count < 2U) {
        return 0U;
    }

    qsort(values, count, sizeof(*values), compare_ints);
    right = count - 1U;

    while (left < right) {
        const int64_t sum =
            (int64_t)values[left] + (int64_t)values[right];

        if (sum < target) {
            ++left;
        } else if (sum > target) {
            --right;
        } else if (values[left] == values[right]) {
            const uint64_t occurrences = (uint64_t)(right - left + 1U);

            pairs += occurrences * (occurrences - 1U) / 2U;
            break;
        } else {
            size_t left_count = 1U;
            size_t right_count = 1U;

            while (left + left_count < right &&
                   values[left + left_count] == values[left]) {
                ++left_count;
            }

            while (right_count < right - left &&
                   values[right - right_count] == values[right]) {
                ++right_count;
            }

            pairs += (uint64_t)left_count * (uint64_t)right_count;
            left += left_count;
            right -= right_count;
        }
    }

    return pairs;
}

static int read_line(char **buffer, size_t *capacity)
{
    size_t length = 0U;
    int ch;

    if (buffer == NULL || capacity == NULL) {
        return 0;
    }

    if (*buffer == NULL || *capacity < 2U) {
        char *new_buffer = malloc(128U);

        if (new_buffer == NULL) {
            return 0;
        }

        free(*buffer);
        *buffer = new_buffer;
        *capacity = 128U;
    }

    for (;;) {
        ch = getchar();

        if (ch == '\n') {
            break;
        }

        if (ch == EOF) {
            if (ferror(stdin) != 0 || length == 0U) {
                return 0;
            }
            break;
        }

        if (length == SIZE_MAX - 1U) {
            return 0;
        }

        if (length + 1U >= *capacity) {
            size_t new_capacity;
            char *new_buffer;

            if (*capacity > SIZE_MAX / 2U) {
                return 0;
            }

            new_capacity = *capacity * 2U;
            new_buffer = realloc(*buffer, new_capacity);

            if (new_buffer == NULL) {
                return 0;
            }

            *buffer = new_buffer;
            *capacity = new_capacity;
        }

        (*buffer)[length++] = (char)ch;
    }

    (*buffer)[length] = '\0';
    return 1;
}

static int next_token(char **cursor, char **token)
{
    char *p;

    if (cursor == NULL || *cursor == NULL || token == NULL) {
        return 0;
    }

    p = *cursor;

    while (*p != '\0' && isspace((unsigned char)*p) != 0) {
        ++p;
    }

    if (*p == '\0') {
        *cursor = p;
        return 0;
    }

    *token = p;

    while (*p != '\0' && isspace((unsigned char)*p) == 0) {
        ++p;
    }

    if (*p != '\0') {
        *p++ = '\0';
    }

    *cursor = p;
    return 1;
}

static int parse_size(const char *text, size_t *value)
{
    char *end = NULL;
    uintmax_t parsed;

    if (text == NULL || value == NULL || *text == '\0' ||
        *text == '-' || *text == '+') {
        return 0;
    }

    errno = 0;
    parsed = strtoumax(text, &end, 10);

    if (errno == ERANGE || end == text || *end != '\0' ||
        parsed > (uintmax_t)SIZE_MAX) {
        return 0;
    }

    *value = (size_t)parsed;
    return 1;
}

static int parse_int64(const char *text, int64_t *value)
{
    char *end = NULL;
    intmax_t parsed;

    if (text == NULL || value == NULL || *text == '\0') {
        return 0;
    }

    errno = 0;
    parsed = strtoimax(text, &end, 10);

    if (errno == ERANGE || end == text || *end != '\0' ||
        parsed < INT64_MIN || parsed > INT64_MAX) {
        return 0;
    }

    *value = (int64_t)parsed;
    return 1;
}

static int parse_int(const char *text, int *value)
{
    char *end = NULL;
    intmax_t parsed;

    if (text == NULL || value == NULL || *text == '\0') {
        return 0;
    }

    errno = 0;
    parsed = strtoimax(text, &end, 10);

    if (errno == ERANGE || end == text || *end != '\0' ||
        parsed < INT_MIN || parsed > INT_MAX) {
        return 0;
    }

    *value = (int)parsed;
    return 1;
}

static int remaining_input_is_whitespace(void)
{
    int ch;

    while ((ch = getchar()) != EOF) {
        if (isspace((unsigned char)ch) == 0) {
            return 0;
        }
    }

    return ferror(stdin) == 0;
}

int main(void)
{
    char *line = NULL;
    size_t line_capacity = 0U;
    char *cursor;
    char *token;
    size_t count;
    int64_t target;
    int *values = NULL;
    int status = EXIT_FAILURE;

    if (!read_line(&line, &line_capacity)) {
        fputs("Invalid input\n", stderr);
        goto cleanup;
    }

    cursor = line;

    if (!next_token(&cursor, &token) ||
        !parse_size(token, &count) ||
        !next_token(&cursor, &token) ||
        !parse_int64(token, &target) ||
        next_token(&cursor, &token)) {
        fputs("Invalid input\n", stderr);
        goto cleanup;
    }

    if (count > SIZE_MAX / sizeof(*values)) {
        fputs("Input size is too large\n", stderr);
        goto cleanup;
    }

    if (count > 0U) {
        values = malloc(count * sizeof(*values));

        if (values == NULL) {
            fputs("Memory allocation failed\n", stderr);
            goto cleanup;
        }
    }

    for (size_t i = 0U; i < count;) {
        if (!read_line(&line, &line_capacity)) {
            fputs("Invalid input\n", stderr);
            goto cleanup;
        }

        cursor = line;

        while (next_token(&cursor, &token)) {
            if (i >= count || !parse_int(token, &values[i])) {
                fputs("Invalid input\n", stderr);
                goto cleanup;
            }

            ++i;
        }
    }

    if (!remaining_input_is_whitespace()) {
        fputs(ferror(stdin) != 0 ? "Input error\n" : "Invalid input\n",
              stderr);
        goto cleanup;
    }

    if (printf("%" PRIu64 "\n",
               count_pairs(values, count, target)) < 0) {
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free(values);
    free(line);
    return status;
}