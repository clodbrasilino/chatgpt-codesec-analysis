#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static uint64_t magnitude(int64_t value)
{
    return value < 0
        ? UINT64_C(0) - (uint64_t)value
        : (uint64_t)value;
}

static uint64_t digit_distance(int64_t first, int64_t second)
{
    uint64_t left = magnitude(first);
    uint64_t right = magnitude(second);
    uint64_t distance = 0;

    do {
        uint64_t left_digit = left % UINT64_C(10);
        uint64_t right_digit = right % UINT64_C(10);

        distance += left_digit > right_digit
            ? left_digit - right_digit
            : right_digit - left_digit;

        left /= UINT64_C(10);
        right /= UINT64_C(10);
    } while (left != 0 || right != 0);

    return distance;
}

static int read_line(FILE *stream, char **line, size_t *capacity)
{
    size_t length = 0;
    int ch;

    if (stream == NULL || line == NULL || capacity == NULL) {
        return 0;
    }

    if (*line == NULL || *capacity < 2) {
        char *allocated;
        size_t initial_capacity = 128;

        allocated = malloc(initial_capacity);
        if (allocated == NULL) {
            return 0;
        }

        free(*line);
        *line = allocated;
        *capacity = initial_capacity;
    }

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stream)) != EOF && ch != '\n') {
        if (length + 1 >= *capacity) {
            size_t new_capacity;
            char *resized;

            if (*capacity > SIZE_MAX / 2) {
                return 0;
            }

            new_capacity = *capacity * 2;
            resized = realloc(*line, new_capacity);
            if (resized == NULL) {
                return 0;
            }

            *line = resized;
            *capacity = new_capacity;
        }

        (*line)[length++] = (char)(unsigned char)ch;
    }

    if (ferror(stream)) {
        return 0;
    }

    if (ch == EOF && length == 0) {
        return 0;
    }

    (*line)[length] = '\0';
    return 1;
}

static int parse_two_int64(const char *line, int64_t *first, int64_t *second)
{
    const char *cursor;
    char *end;
    intmax_t parsed;

    if (line == NULL || first == NULL || second == NULL) {
        return 0;
    }

    cursor = line;

    while (isspace((unsigned char)*cursor)) {
        ++cursor;
    }

    errno = 0;
    parsed = strtoimax(cursor, &end, 10);
    if (end == cursor || errno == ERANGE ||
        parsed < INT64_MIN || parsed > INT64_MAX) {
        return 0;
    }

    *first = (int64_t)parsed;
    cursor = end;

    if (*cursor == '\0' || !isspace((unsigned char)*cursor)) {
        return 0;
    }

    while (isspace((unsigned char)*cursor)) {
        ++cursor;
    }

    errno = 0;
    parsed = strtoimax(cursor, &end, 10);
    if (end == cursor || errno == ERANGE ||
        parsed < INT64_MIN || parsed > INT64_MAX) {
        return 0;
    }

    *second = (int64_t)parsed;
    cursor = end;

    while (isspace((unsigned char)*cursor)) {
        ++cursor;
    }

    return *cursor == '\0';
}

static int remaining_input_is_whitespace(FILE *stream)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    unsigned char buffer[4096];
    size_t count;

    if (stream == NULL) {
        return 0;
    }

    while ((count = fread(buffer, 1, sizeof(buffer), stream)) != 0) {
        size_t i;

        for (i = 0; i < count; ++i) {
            if (!isspace(buffer[i])) {
                return 0;
            }
        }
    }

    return !ferror(stream);
}

int main(void)
{
    char *line = NULL;
    size_t capacity = 0;
    int64_t first;
    int64_t second;
    int result = EXIT_FAILURE;

    if (!read_line(stdin, &line, &capacity) ||
        !parse_two_int64(line, &first, &second) ||
        !remaining_input_is_whitespace(stdin)) {
        fputs("Invalid input\n", stderr);
        goto cleanup;
    }

    if (printf("%" PRIu64 "\n", digit_distance(first, second)) < 0) {
        goto cleanup;
    }

    result = EXIT_SUCCESS;

cleanup:
    free(line);
    return result;
}