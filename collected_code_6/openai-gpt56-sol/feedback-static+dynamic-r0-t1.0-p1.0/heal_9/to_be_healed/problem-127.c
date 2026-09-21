#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int multiply_int64(int64_t left, int64_t right, int64_t *result)
{
    if (result == NULL) {
        return 0;
    }

#if defined(__GNUC__) || defined(__clang__)
    return !__builtin_mul_overflow(left, right, result);
#else
    if (left > 0) {
        if ((right > 0 && left > INT64_MAX / right) ||
            (right < 0 && right < INT64_MIN / left)) {
            return 0;
        }
    } else if (left < 0) {
        if ((right > 0 && left < INT64_MIN / right) ||
            (right < 0 && left < INT64_MAX / right)) {
            return 0;
        }
    }

    *result = left * right;
    return 1;
#endif
}

static int discard_line(void)
{
    int ch;

    do {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);
    } while (ch != '\n' && ch != EOF);

    return ch == '\n' || !ferror(stdin);
}

static int read_line(char **line, size_t *capacity)
{
    size_t length = 0;
    int ch;

    if (line == NULL || capacity == NULL) {
        return 0;
    }

    *capacity = 128;
    *line = malloc(*capacity);

    if (*line == NULL) {
        return 0;
    }

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stdin)) != EOF && ch != '\n') {
        if (length == SIZE_MAX - 1) {
            free(*line);
            *line = NULL;
            *capacity = 0;
            discard_line();
            return 0;
        }

        if (length + 1 >= *capacity) {
            size_t new_capacity;
            char *new_line;

            if (*capacity > SIZE_MAX / 2) {
                free(*line);
                *line = NULL;
                *capacity = 0;
                discard_line();
                return 0;
            }

            new_capacity = *capacity * 2;
            new_line = realloc(*line, new_capacity);

            if (new_line == NULL) {
                free(*line);
                *line = NULL;
                *capacity = 0;
                discard_line();
                return 0;
            }

            *line = new_line;
            *capacity = new_capacity;
        }

        (*line)[length++] = (char)ch;
    }

    if (ch == EOF && ferror(stdin)) {
        free(*line);
        *line = NULL;
        *capacity = 0;
        return 0;
    }

    (*line)[length] = '\0';

    if (length == 0 && ch == EOF) {
        free(*line);
        *line = NULL;
        *capacity = 0;
        return 0;
    }

    return 1;
}

static int is_space(unsigned char ch)
{
    return ch == ' ' || ch == '\t' || ch == '\n' ||
           ch == '\r' || ch == '\f' || ch == '\v';
}

static int only_whitespace_remaining(void)
{
    int ch;

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stdin)) != EOF) {
        if (!is_space((unsigned char)ch)) {
            return 0;
        }
    }

    return !ferror(stdin);
}

static int parse_int64_line(int64_t *left, int64_t *right)
{
    char *line = NULL;
    size_t capacity = 0;
    char *cursor;
    char *end;
    intmax_t parsed;
    int valid = 0;

    if (left == NULL || right == NULL) {
        return 0;
    }

    if (!read_line(&line, &capacity)) {
        return 0;
    }

    cursor = line;

    while (is_space((unsigned char)*cursor)) {
        ++cursor;
    }

    errno = 0;
    parsed = strtoimax(cursor, &end, 10);

    if (end == cursor || errno == ERANGE ||
        parsed < INT64_MIN || parsed > INT64_MAX) {
        goto cleanup;
    }

    *left = (int64_t)parsed;
    cursor = end;

    while (is_space((unsigned char)*cursor)) {
        ++cursor;
    }

    errno = 0;
    parsed = strtoimax(cursor, &end, 10);

    if (end == cursor || errno == ERANGE ||
        parsed < INT64_MIN || parsed > INT64_MAX) {
        goto cleanup;
    }

    *right = (int64_t)parsed;
    cursor = end;

    while (is_space((unsigned char)*cursor)) {
        ++cursor;
    }

    if (*cursor != '\0') {
        goto cleanup;
    }

    valid = only_whitespace_remaining();

cleanup:
    free(line);
    return valid;
}

int main(void)
{
    int64_t left;
    int64_t right;
    int64_t result;

    if (!parse_int64_line(&left, &right)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (!multiply_int64(left, right, &result)) {
        fputs("Multiplication overflow\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%" PRId64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}