#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static uint64_t magnitude(int64_t value)
{
    if (value >= 0) {
        return (uint64_t)value;
    }

    return UINT64_C(0) - (uint64_t)value;
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
    int ch = EOF;

    if (stream == NULL || line == NULL || capacity == NULL) {
        return 0;
    }

    if (*line == NULL || *capacity < 2) {
        size_t initial_capacity = 128;
        char *buffer = malloc(initial_capacity);

        if (buffer == NULL) {
            return 0;
        }

        free(*line);
        *line = buffer;
        *capacity = initial_capacity;
    }

    for (;;) {
        ch = fgetc(stream);

        if (ch == EOF || ch == '\n') {
            break;
        }

        if (length == SIZE_MAX - 1) {
            return 0;
        }

        if (length + 1 >= *capacity) {
            size_t required = length + 2;
            size_t new_capacity = *capacity;
            char *buffer;

            while (new_capacity < required) {
                if (new_capacity > SIZE_MAX / 2) {
                    new_capacity = required;
                    break;
                }

                new_capacity *= 2;
            }

            buffer = realloc(*line, new_capacity);
            if (buffer == NULL) {
                return 0;
            }

            *line = buffer;
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
    intmax_t parsed_first;
    intmax_t parsed_second;

    if (line == NULL || first == NULL || second == NULL) {
        return 0;
    }

    cursor = line;

    while (isspace((unsigned char)*cursor)) {
        ++cursor;
    }

    errno = 0;
    parsed_first = strtoimax(cursor, &end, 10);

    if (end == cursor || errno == ERANGE ||
        parsed_first < INT64_MIN || parsed_first > INT64_MAX) {
        return 0;
    }

    cursor = end;

    if (*cursor == '\0' || !isspace((unsigned char)*cursor)) {
        return 0;
    }

    while (isspace((unsigned char)*cursor)) {
        ++cursor;
    }

    errno = 0;
    parsed_second = strtoimax(cursor, &end, 10);

    if (end == cursor || errno == ERANGE ||
        parsed_second < INT64_MIN || parsed_second > INT64_MAX) {
        return 0;
    }

    cursor = end;

    while (isspace((unsigned char)*cursor)) {
        ++cursor;
    }

    if (*cursor != '\0') {
        return 0;
    }

    *first = (int64_t)parsed_first;
    *second = (int64_t)parsed_second;
    return 1;
}

static int remaining_input_is_whitespace(FILE *stream)
{
    unsigned char buffer[4096];
    size_t count;

    if (stream == NULL) {
        return 0;
    }

    while ((count = fread(buffer, 1, sizeof buffer, stream)) != 0) {
        size_t i;

        for (i = 0; i < count; ++i) {
            if (!isspace(buffer[i])) {
                return 0;
            }
        }
    }

    return ferror(stream) == 0;
}

int main(void)
{
    char *line = NULL;
    size_t capacity = 0;
    int64_t first;
    int64_t second;
    int status = EXIT_FAILURE;

    if (!read_line(stdin, &line, &capacity) ||
        !parse_two_int64(line, &first, &second) ||
        !remaining_input_is_whitespace(stdin)) {
        fputs("Invalid input\n", stderr);
        goto cleanup;
    }

    if (printf("%" PRIu64 "\n", digit_distance(first, second)) < 0) {
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free(line);
    return status;
}