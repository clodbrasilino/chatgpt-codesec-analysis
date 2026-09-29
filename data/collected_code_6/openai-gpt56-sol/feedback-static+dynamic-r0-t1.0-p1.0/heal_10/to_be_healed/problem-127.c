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

static int read_line(char **line)
{
    size_t capacity = 128;
    size_t length = 0;
    char *buffer;
    int ch;

    if (line == NULL) {
        return 0;
    }

    *line = NULL;
    buffer = malloc(capacity);

    if (buffer == NULL) {
        return 0;
    }

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stdin)) != EOF && ch != '\n') {
        if (length >= capacity - 1) {
            size_t new_capacity;
            char *new_buffer;

            if (capacity > SIZE_MAX / 2) {
                free(buffer);
                return 0;
            }

            new_capacity = capacity * 2;
            new_buffer = realloc(buffer, new_capacity);

            if (new_buffer == NULL) {
                free(buffer);
                return 0;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        buffer[length++] = (char)ch;
    }

    if (ferror(stdin) || (ch == EOF && length == 0)) {
        free(buffer);
        return 0;
    }

    buffer[length] = '\0';
    *line = buffer;
    return 1;
}

static int is_space(unsigned char ch)
{
    return ch == ' ' || ch == '\t' || ch == '\n' ||
           ch == '\r' || ch == '\f' || ch == '\v';
}

static int only_whitespace_remaining(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    unsigned char buffer[4096];
    size_t count;
    size_t i;

    while ((count = fread(buffer, 1, sizeof(buffer), stdin)) != 0) {
        for (i = 0; i < count; ++i) {
            if (!is_space(buffer[i])) {
                return 0;
            }
        }
    }

    return !ferror(stdin);
}

static int parse_int64_line(int64_t *left, int64_t *right)
{
    char *line = NULL;
    char *cursor;
    char *end;
    intmax_t parsed;
    int valid = 0;

    if (left == NULL || right == NULL || !read_line(&line)) {
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

    if (*cursor == '\0') {
        valid = only_whitespace_remaining();
    }

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