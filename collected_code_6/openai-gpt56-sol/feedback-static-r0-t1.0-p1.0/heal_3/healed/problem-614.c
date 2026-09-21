#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <stddef.h>
#include <errno.h>
#include <ctype.h>

typedef struct {
    int64_t first;
    int64_t second;
} Tuple;

static int read_line(char **line, size_t *capacity)
{
    size_t length = 0;
    int ch = EOF;

    if (line == NULL || capacity == NULL) {
        return 0;
    }

    if (*line == NULL || *capacity == 0) {
        *capacity = 128;
        *line = malloc(*capacity);
        if (*line == NULL) {
            *capacity = 0;
            return 0;
        }
    }

    for (;;) {
        ch = fgetc(stdin);

        if (ch == EOF) {
            if (ferror(stdin) || length == 0) {
                return 0;
            }
            break;
        }

        if (length == SIZE_MAX - 1) {
            return 0;
        }

        if (length + 1 >= *capacity) {
            size_t required = length + 2;
            size_t new_capacity;
            char *new_line;

            if (*capacity > SIZE_MAX / 2) {
                new_capacity = SIZE_MAX;
            } else {
                new_capacity = *capacity * 2;
            }

            if (new_capacity < required) {
                return 0;
            }

            new_line = realloc(*line, new_capacity);
            if (new_line == NULL) {
                return 0;
            }

            *line = new_line;
            *capacity = new_capacity;
        }

        (*line)[length++] = (char)ch;

        if (ch == '\n') {
            break;
        }
    }

    (*line)[length] = '\0';
    return 1;
}

static int only_trailing_whitespace(const char *text)
{
    if (text == NULL) {
        return 0;
    }

    while (*text != '\0') {
        if (!isspace((unsigned char)*text)) {
            return 0;
        }
        ++text;
    }

    return 1;
}

static int read_size(size_t *value)
{
    char *line = NULL;
    size_t capacity = 0;
    char *cursor;
    char *end;
    uintmax_t parsed;
    int success = 0;

    if (value == NULL || !read_line(&line, &capacity)) {
        free(line);
        return 0;
    }

    cursor = line;
    while (isspace((unsigned char)*cursor)) {
        ++cursor;
    }

    if (*cursor == '-') {
        free(line);
        return 0;
    }

    errno = 0;
    parsed = strtoumax(cursor, &end, 10);

    if (errno != ERANGE &&
        end != cursor &&
        parsed <= SIZE_MAX &&
        only_trailing_whitespace(end)) {
        *value = (size_t)parsed;
        success = 1;
    }

    free(line);
    return success;
}

static int read_tuple(Tuple *tuple)
{
    char *line = NULL;
    size_t capacity = 0;
    char *cursor;
    char *end;
    intmax_t first;
    intmax_t second;
    int success = 0;

    if (tuple == NULL || !read_line(&line, &capacity)) {
        free(line);
        return 0;
    }

    cursor = line;
    errno = 0;
    first = strtoimax(cursor, &end, 10);

    if (errno == ERANGE ||
        end == cursor ||
        first < INT64_MIN ||
        first > INT64_MAX) {
        free(line);
        return 0;
    }

    cursor = end;
    errno = 0;
    second = strtoimax(cursor, &end, 10);

    if (errno != ERANGE &&
        end != cursor &&
        second >= INT64_MIN &&
        second <= INT64_MAX &&
        only_trailing_whitespace(end)) {
        tuple->first = (int64_t)first;
        tuple->second = (int64_t)second;
        success = 1;
    }

    free(line);
    return success;
}

static int add_int64(int64_t left, int64_t right, int64_t *result)
{
    if (result == NULL) {
        return 0;
    }

    if ((right > 0 && left > INT64_MAX - right) ||
        (right < 0 && left < INT64_MIN - right)) {
        return 0;
    }

    *result = left + right;
    return 1;
}

static int cumulative_sum(const Tuple *tuples, size_t count, int64_t *result)
{
    int64_t sum = 0;

    if (result == NULL || (tuples == NULL && count != 0)) {
        return 0;
    }

    for (size_t i = 0; i < count; ++i) {
        if (!add_int64(sum, tuples[i].first, &sum) ||
            !add_int64(sum, tuples[i].second, &sum)) {
            return 0;
        }
    }

    *result = sum;
    return 1;
}

int main(void)
{
    size_t count;
    Tuple *tuples = NULL;
    int64_t sum;

    if (!read_size(&count)) {
        return EXIT_FAILURE;
    }

    if (count > SIZE_MAX / sizeof(*tuples)) {
        return EXIT_FAILURE;
    }

    if (count != 0) {
        tuples = malloc(count * sizeof(*tuples));
        if (tuples == NULL) {
            return EXIT_FAILURE;
        }
    }

    for (size_t i = 0; i < count; ++i) {
        if (!read_tuple(&tuples[i])) {
            free(tuples);
            return EXIT_FAILURE;
        }
    }

    if (!cumulative_sum(tuples, count, &sum)) {
        free(tuples);
        return EXIT_FAILURE;
    }

    if (printf("%" PRId64 "\n", sum) < 0) {
        free(tuples);
        return EXIT_FAILURE;
    }

    free(tuples);
    return EXIT_SUCCESS;
}