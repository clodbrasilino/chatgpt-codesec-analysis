#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  include '<string.h>' or provide a declaration of 'strlen'
  */

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

    if (*line == NULL || *capacity == 0) {
        *capacity = 128;
        *line = malloc(*capacity);
        if (*line == NULL) {
            return 0;
        }
    }

    (*line)[0] = '\0';

    for (;;) {
        if (fgets(*line + length, *capacity - length, stdin) == NULL) {
            return 0;
        }

        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         *  implicit declaration of function 'strlen' [-Wimplicit-function-declaration]
         *  call to undeclared library function 'strlen' with type 'unsigned long (const char *)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
         *  include the header <string.h> or explicitly provide a declaration for 'strlen'
         */
        length += strlen(*line + length);

        if (length > 0 && (*line)[length - 1] == '\n') {
            return 1;
        }

        if (feof(stdin)) {
            return 1;
        }

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
    }
}

static int trailing_input_is_valid(const char *end)
{
    while (*end == ' ' || *end == '\t' || *end == '\r') {
        ++end;
    }

    return *end == '\n' || *end == '\0';
}

static int read_int64(int64_t *value)
{
    char *line = NULL;
    size_t capacity = 0;
    char *end;
    int success = 0;

    if (value == NULL || !read_line(&line, &capacity)) {
        free(line);
        return 0;
    }

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
    char *end;
    int success = 0;

    if (value == NULL || !read_line(&line, &capacity)) {
        free(line);
        return 0;
    }

    errno = 0;
    uintmax_t parsed = strtoumax(line, &end, 10);

    const char *start = line;
    while (*start == ' ' || *start == '\t' ||
           *start == '\r' || *start == '\n' ||
           *start == '\f' || *start == '\v') {
        ++start;
    }

    if (*start != '-' &&
        end != line &&
        errno != ERANGE &&
        parsed <= SIZE_MAX &&
        trailing_input_is_valid(end)) {
        *value = (size_t)parsed;
        success = 1;
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
    size_t length;

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