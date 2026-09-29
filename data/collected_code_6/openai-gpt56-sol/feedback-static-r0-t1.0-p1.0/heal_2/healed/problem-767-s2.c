#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <stddef.h>
#include <errno.h>
#include <ctype.h>
#include <limits.h>
#include <string.h>

static int compare_ints(const void *lhs, const void *rhs)
{
    const int a = *(const int *)lhs;
    const int b = *(const int *)rhs;

    return (a > b) - (a < b);
}

static uint64_t count_pairs(int *values, size_t count, int64_t target)
{
    size_t left = 0;
    size_t right;
    uint64_t pairs = 0;

    if (values == NULL || count < 2) {
        return 0;
    }

    qsort(values, count, sizeof(*values), compare_ints);
    right = count - 1;

    while (left < right) {
        const int64_t current =
            (int64_t)values[left] + (int64_t)values[right];

        if (current < target) {
            ++left;
        } else if (current > target) {
            --right;
        } else if (values[left] == values[right]) {
            const uint64_t occurrences = (uint64_t)(right - left + 1);
            pairs += occurrences * (occurrences - 1U) / 2U;
            break;
        } else {
            size_t left_count = 1;
            size_t right_count = 1;

            while (left + left_count < right &&
                   values[left + left_count] == values[left]) {
                ++left_count;
            }

            while (right > left + left_count &&
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

static int read_line(char *buffer, size_t size)
{
    size_t length;
    int ch;

    if (buffer == NULL || size < 2U) {
        return 0;
    }

    if (fgets(buffer, (int)size, stdin) == NULL) {
        return 0;
    }

    length = strlen(buffer);

    if (length > 0U && buffer[length - 1U] == '\n') {
        buffer[length - 1U] = '\0';
        return 1;
    }

    if (feof(stdin)) {
        return 1;
    }

    do {
        ch = fgetc(stdin);
    } while (ch != '\n' && ch != EOF);

    buffer[0] = '\0';
    return 0;
}

static int next_token(char **cursor, char **token)
{
    char *p;

    if (cursor == NULL || *cursor == NULL || token == NULL) {
        return 0;
    }

    p = *cursor;

    while (*p != '\0' && isspace((unsigned char)*p)) {
        ++p;
    }

    if (*p == '\0') {
        *cursor = p;
        return 0;
    }

    *token = p;

    while (*p != '\0' && !isspace((unsigned char)*p)) {
        ++p;
    }

    if (*p != '\0') {
        *p = '\0';
        ++p;
    }

    *cursor = p;
    return 1;
}

static int parse_size(const char *text, size_t *value)
{
    char *end;
    uintmax_t parsed;

    if (text == NULL || value == NULL || *text == '\0' ||
        *text == '-' || *text == '+') {
        return 0;
    }

    errno = 0;
    parsed = strtoumax(text, &end, 10);

    if (errno == ERANGE || end == text || *end != '\0' ||
        parsed > SIZE_MAX) {
        return 0;
    }

    *value = (size_t)parsed;
    return 1;
}

static int parse_int64(const char *text, int64_t *value)
{
    char *end;
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
    char *end;
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

int main(void)
{
    enum { LINE_SIZE = 4096 };
    char line[LINE_SIZE];
    char *cursor;
    char *token;
    size_t count;
    int64_t target;
    int *values = NULL;

    if (!read_line(line, sizeof(line))) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    cursor = line;

    if (!next_token(&cursor, &token) ||
        !parse_size(token, &count) ||
        !next_token(&cursor, &token) ||
        !parse_int64(token, &target) ||
        next_token(&cursor, &token)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (count > SIZE_MAX / sizeof(*values)) {
        fputs("Input size is too large\n", stderr);
        return EXIT_FAILURE;
    }

    if (count > 0U) {
        values = malloc(count * sizeof(*values));
        if (values == NULL) {
            fputs("Memory allocation failed\n", stderr);
            return EXIT_FAILURE;
        }
    }

    for (size_t i = 0; i < count;) {
        if (!read_line(line, sizeof(line))) {
            fputs("Invalid input\n", stderr);
            free(values);
            return EXIT_FAILURE;
        }

        cursor = line;

        while (next_token(&cursor, &token)) {
            if (i >= count || !parse_int(token, &values[i])) {
                fputs("Invalid input\n", stderr);
                free(values);
                return EXIT_FAILURE;
            }

            ++i;
        }
    }

    for (;;) {
        int ch = fgetc(stdin);

        if (ch == EOF) {
            if (ferror(stdin)) {
                fputs("Input error\n", stderr);
                free(values);
                return EXIT_FAILURE;
            }
            break;
        }

        if (!isspace((unsigned char)ch)) {
            fputs("Invalid input\n", stderr);
            free(values);
            return EXIT_FAILURE;
        }
    }

    {
        const uint64_t result = count_pairs(values, count, target);

        if (printf("%" PRIu64 "\n", result) < 0) {
            free(values);
            return EXIT_FAILURE;
        }
    }

    free(values);
    return EXIT_SUCCESS;
}