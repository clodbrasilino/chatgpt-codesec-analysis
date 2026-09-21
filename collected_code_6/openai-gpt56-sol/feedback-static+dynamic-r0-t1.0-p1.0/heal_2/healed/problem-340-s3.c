#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <stddef.h>
#include <limits.h>
#include <ctype.h>
#include <errno.h>

static int read_line(char **line, size_t *capacity)
{
    if (line == NULL || capacity == NULL) {
        return -1;
    }

    size_t length = 0;

    for (;;) {
        if (length == *capacity) {
            size_t new_capacity;

            if (*capacity == 0) {
                new_capacity = 64;
            } else {
                if (*capacity > SIZE_MAX / 2) {
                    free(*line);
                    *line = NULL;
                    *capacity = 0;
                    return -1;
                }
                new_capacity = *capacity * 2;
            }

            char *new_line = realloc(*line, new_capacity);
            if (new_line == NULL) {
                free(*line);
                *line = NULL;
                *capacity = 0;
                return -1;
            }

            *line = new_line;
            *capacity = new_capacity;
        }

        int ch = fgetc(stdin);

        if (ch == EOF) {
            if (ferror(stdin) || length == 0) {
                return -1;
            }
            break;
        }

        if (ch == '\n') {
            break;
        }

        (*line)[length++] = (char)ch;
    }

    if (length == *capacity) {
        if (*capacity == SIZE_MAX) {
            free(*line);
            *line = NULL;
            *capacity = 0;
            return -1;
        }

        char *new_line = realloc(*line, *capacity + 1);
        if (new_line == NULL) {
            free(*line);
            *line = NULL;
            *capacity = 0;
            return -1;
        }

        *line = new_line;
        ++*capacity;
    }

    (*line)[length] = '\0';
    return 0;
}

static int has_only_trailing_space(const char *text)
{
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
    if (value == NULL) {
        return -1;
    }

    char *line = NULL;
    size_t capacity = 0;

    if (read_line(&line, &capacity) != 0) {
        free(line);
        return -1;
    }

    char *start = line;

    while (isspace((unsigned char)*start)) {
        ++start;
    }

    if (*start == '-' || *start == '\0') {
        free(line);
        return -1;
    }

    errno = 0;
    char *end = NULL;
    uintmax_t parsed = strtoumax(start, &end, 10);

    if (end == start || errno == ERANGE ||
        parsed > SIZE_MAX || !has_only_trailing_space(end)) {
        free(line);
        return -1;
    }

    *value = (size_t)parsed;
    free(line);
    return 0;
}

static int read_int64(int64_t *value)
{
    if (value == NULL) {
        return -1;
    }

    char *line = NULL;
    size_t capacity = 0;

    if (read_line(&line, &capacity) != 0) {
        free(line);
        return -1;
    }

    char *start = line;

    while (isspace((unsigned char)*start)) {
        ++start;
    }

    if (*start == '\0') {
        free(line);
        return -1;
    }

    errno = 0;
    char *end = NULL;
    intmax_t parsed = strtoimax(start, &end, 10);

    if (end == start || errno == ERANGE ||
        parsed < INT64_MIN || parsed > INT64_MAX ||
        !has_only_trailing_space(end)) {
        free(line);
        return -1;
    }

    *value = (int64_t)parsed;
    free(line);
    return 0;
}

static int sum_three_lowest_positive(const int64_t *numbers,
                                     size_t count,
                                     int64_t *sum)
{
    if (sum == NULL || (numbers == NULL && count != 0)) {
        return -1;
    }

    int64_t lowest[3] = {INT64_MAX, INT64_MAX, INT64_MAX};
    size_t positives = 0;

    for (size_t i = 0; i < count; ++i) {
        int64_t value = numbers[i];

        if (value <= 0) {
            continue;
        }

        if (positives < 3) {
            ++positives;
        }

        if (value < lowest[0]) {
            lowest[2] = lowest[1];
            lowest[1] = lowest[0];
            lowest[0] = value;
        } else if (value < lowest[1]) {
            lowest[2] = lowest[1];
            lowest[1] = value;
        } else if (value < lowest[2]) {
            lowest[2] = value;
        }
    }

    if (positives < 3) {
        return 1;
    }

    if (lowest[0] > INT64_MAX - lowest[1]) {
        return 2;
    }

    int64_t partial = lowest[0] + lowest[1];

    if (partial > INT64_MAX - lowest[2]) {
        return 2;
    }

    *sum = partial + lowest[2];
    return 0;
}

int main(void)
{
    size_t count;

    if (read_size(&count) != 0 ||
        count > SIZE_MAX / sizeof(int64_t)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    int64_t *numbers = NULL;

    if (count != 0) {
        numbers = malloc(count * sizeof *numbers);

        if (numbers == NULL) {
            fputs("Memory allocation failed\n", stderr);
            return EXIT_FAILURE;
        }
    }

    for (size_t i = 0; i < count; ++i) {
        if (read_int64(&numbers[i]) != 0) {
            fputs("Invalid input\n", stderr);
            free(numbers);
            return EXIT_FAILURE;
        }
    }

    int64_t sum;
    int result = sum_three_lowest_positive(numbers, count, &sum);

    free(numbers);

    if (result == 1) {
        fputs("Fewer than three positive numbers\n", stderr);
        return EXIT_FAILURE;
    }

    if (result == 2) {
        fputs("Sum overflow\n", stderr);
        return EXIT_FAILURE;
    }

    if (result != 0) {
        fputs("Invalid arguments\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%" PRId64 "\n", sum) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}