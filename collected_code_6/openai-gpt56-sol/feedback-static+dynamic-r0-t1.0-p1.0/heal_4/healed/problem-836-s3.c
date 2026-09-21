#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int add_overflows_int64(int64_t a, int64_t b)
{
    return (b > 0 && a > INT64_MAX - b) ||
           (b < 0 && a < INT64_MIN - b);
}

static int read_line(char **line, size_t *capacity)
{
    size_t length = 0;

    if (line == NULL || capacity == NULL) {
        return 0;
    }

    if (*line == NULL || *capacity < 2) {
        size_t initial_capacity = 128;
        char *new_line = realloc(*line, initial_capacity);

        if (new_line == NULL) {
            return 0;
        }

        *line = new_line;
        *capacity = initial_capacity;
    }

    (*line)[0] = '\0';

    for (;;) {
        size_t available = *capacity - length;

        if (available < 2) {
            if (*capacity > SIZE_MAX / 2) {
                return 0;
            }

            size_t new_capacity = *capacity * 2;
            char *new_line = realloc(*line, new_capacity);

            if (new_line == NULL) {
                return 0;
            }

            *line = new_line;
            *capacity = new_capacity;
            available = *capacity - length;
        }

        if (fgets(*line + length, available, stdin) == NULL) {
            return length > 0 && feof(stdin);
        }

        size_t added = strnlen(*line + length, available);
        if (added == available) {
            return 0;
        }

        length += added;

        if (length > 0 && (*line)[length - 1] == '\n') {
            return 1;
        }

        if (feof(stdin)) {
            return 1;
        }
    }
}

static int trailing_input_is_valid(const char *end)
{
    if (end == NULL) {
        return 0;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r') {
        ++end;
    }

    return *end == '\n' || *end == '\0';
}

static int read_int64(int64_t *value)
{
    char *line = NULL;
    size_t capacity = 0;
    int success = 0;

    if (value == NULL || !read_line(&line, &capacity)) {
        free(line);
        return 0;
    }

    char *end = NULL;
    errno = 0;
    intmax_t parsed = strtoimax(line, &end, 10);

    if (end != line &&
        errno != ERANGE &&
        parsed >= INT64_MIN &&
        parsed <= INT64_MAX &&
        trailing_input_is_valid(end)) {
        *value = (int64_t)parsed;
        success = 1;
    }

    free(line);
    return success;
}

static int read_size(size_t *value)
{
    char *line = NULL;
    size_t capacity = 0;
    int success = 0;

    if (value == NULL || !read_line(&line, &capacity)) {
        free(line);
        return 0;
    }

    const char *start = line;

    while (*start == ' ' || *start == '\t' ||
           *start == '\r' || *start == '\n' ||
           *start == '\f' || *start == '\v') {
        ++start;
    }

    if (*start != '-') {
        char *end = NULL;
        errno = 0;
        uintmax_t parsed = strtoumax(line, &end, 10);

        if (end != line &&
            errno != ERANGE &&
            parsed <= SIZE_MAX &&
            trailing_input_is_valid(end)) {
            *value = (size_t)parsed;
            success = 1;
        }
    }

    free(line);
    return success;
}

static size_t max_sum_subarray_length(const int64_t *array, size_t length)
{
    if (array == NULL || length == 0) {
        return 0;
    }

    int64_t current_sum = array[0];
    int64_t maximum_sum = array[0];
    size_t current_start = 0;
    size_t best_length = 1;

    for (size_t i = 1; i < length; ++i) {
        if (current_sum < 0 ||
            add_overflows_int64(current_sum, array[i])) {
            current_sum = array[i];
            current_start = i;
        } else {
            current_sum += array[i];
        }

        size_t current_length = i - current_start + 1;

        if (current_sum > maximum_sum ||
            (current_sum == maximum_sum &&
             current_length > best_length)) {
            maximum_sum = current_sum;
            best_length = current_length;
        }
    }

    return best_length;
}

int main(void)
{
    size_t length = 0;

    if (!read_size(&length) ||
        length == 0 ||
        length > SIZE_MAX / sizeof(int64_t)) {
        return EXIT_FAILURE;
    }

    int64_t *array = malloc(length * sizeof(*array));

    if (array == NULL) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < length; ++i) {
        if (!read_int64(&array[i])) {
            free(array);
            return EXIT_FAILURE;
        }
    }

    size_t result = max_sum_subarray_length(array, length);

    if (printf("%zu\n", result) < 0) {
        free(array);
        return EXIT_FAILURE;
    }

    free(array);
    return EXIT_SUCCESS;
}