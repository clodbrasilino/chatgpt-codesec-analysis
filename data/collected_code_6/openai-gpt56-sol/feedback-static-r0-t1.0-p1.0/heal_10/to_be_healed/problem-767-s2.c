#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <stddef.h>
#include <errno.h>
#include <ctype.h>
#include <limits.h>
 /* Possible weaknesses found:
  *  include '<string.h>' or provide a declaration of 'strlen'
  */

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

            while (left_count < right - left &&
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
        if (fgets(*buffer + length,
                  (int)((*capacity - length > (size_t)INT_MAX)
                            ? (size_t)INT_MAX
                            : *capacity - length),
                  stdin) == NULL) {
            if (ferror(stdin) != 0 || length == 0U) {
                return 0;
            }

            (*buffer)[length] = '\0';
            return 1;
        }

        /* Possible weaknesses found:
         *  include the header <string.h> or explicitly provide a declaration for 'strlen'
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         *  implicit declaration of function 'strlen' [-Wimplicit-function-declaration]
         *  call to undeclared library function 'strlen' with type 'unsigned long (const char *)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
         */
        length += strlen(*buffer + length);

        if (length > 0U && (*buffer)[length - 1U] == '\n') {
            (*buffer)[length - 1U] = '\0';
            return 1;
        }

        if (feof(stdin) != 0) {
            return 1;
        }

        if (*capacity > SIZE_MAX / 2U) {
            return 0;
        }

        {
            const size_t new_capacity = *capacity * 2U;
            char *new_buffer = realloc(*buffer, new_capacity);

            if (new_buffer == NULL) {
                return 0;
            }

            *buffer = new_buffer;
            *capacity = new_capacity;
        }
    }
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
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[4096];

    while (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        const unsigned char *p = (const unsigned char *)buffer;

        while (*p != '\0') {
            if (isspace(*p) == 0) {
                return 0;
            }
            ++p;
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