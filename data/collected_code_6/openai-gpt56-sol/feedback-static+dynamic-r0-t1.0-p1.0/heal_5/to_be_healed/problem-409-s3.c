#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int64_t first;
    int64_t second;
} Tuple;

static int read_line(char **line, size_t *capacity)
{
    size_t length = 0;
    int ch;

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

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stdin)) != EOF && ch != '\n') {
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

        (*line)[length++] = (char)ch;
    }

    if (ch == EOF && length == 0) {
        return 0;
    }

    (*line)[length] = '\0';
    return 1;
}

static char *skip_horizontal_space(char *text)
{
    while (*text == ' ' || *text == '\t' || *text == '\r') {
        ++text;
    }

    return text;
}

static int multiply_checked(int64_t a, int64_t b, int64_t *result)
{
    if (result == NULL) {
        return 0;
    }

    if (a > 0) {
        if ((b > 0 && a > INT64_MAX / b) ||
            (b < 0 && b < INT64_MIN / a)) {
            return 0;
        }
    } else if (a < 0) {
        if ((b > 0 && a < INT64_MIN / b) ||
            (b < 0 && a < INT64_MAX / b)) {
            return 0;
        }
    }

    *result = a * b;
    return 1;
}

static int minimum_tuple_product(const Tuple *tuples, size_t count,
                                 int64_t *minimum)
{
    int64_t product;

    if (tuples == NULL || minimum == NULL || count == 0) {
        return 0;
    }

    if (!multiply_checked(tuples[0].first, tuples[0].second, minimum)) {
        return 0;
    }

    for (size_t i = 1; i < count; ++i) {
        if (!multiply_checked(tuples[i].first, tuples[i].second, &product)) {
            return 0;
        }

        if (product < *minimum) {
            *minimum = product;
        }
    }

    return 1;
}

static int read_size(size_t *value)
{
    char *line = NULL;
    size_t capacity = 0;
    char *start;
    char *end;
    uintmax_t parsed;
    int success = 0;

    if (value == NULL || !read_line(&line, &capacity)) {
        free(line);
        return 0;
    }

    start = skip_horizontal_space(line);

    if (*start == '-') {
        goto cleanup;
    }

    errno = 0;
    parsed = strtoumax(start, &end, 10);

    if (errno == ERANGE || end == start || parsed == 0 ||
        parsed > (uintmax_t)SIZE_MAX) {
        goto cleanup;
    }

    end = skip_horizontal_space(end);
    if (*end != '\0') {
        goto cleanup;
    }

    *value = (size_t)parsed;
    success = 1;

cleanup:
    free(line);
    return success;
}

static int read_tuple(Tuple *tuple)
{
    char *line = NULL;
    size_t capacity = 0;
    char *cursor;
    char *first_end;
    char *second_end;
    intmax_t first;
    intmax_t second;
    int success = 0;

    if (tuple == NULL || !read_line(&line, &capacity)) {
        free(line);
        return 0;
    }

    cursor = skip_horizontal_space(line);

    errno = 0;
    first = strtoimax(cursor, &first_end, 10);
    if (errno == ERANGE || first_end == cursor ||
        first < INT64_MIN || first > INT64_MAX) {
        goto cleanup;
    }

    cursor = skip_horizontal_space(first_end);
    if (cursor == first_end) {
        goto cleanup;
    }

    errno = 0;
    second = strtoimax(cursor, &second_end, 10);
    if (errno == ERANGE || second_end == cursor ||
        second < INT64_MIN || second > INT64_MAX) {
        goto cleanup;
    }

    second_end = skip_horizontal_space(second_end);
    if (*second_end != '\0') {
        goto cleanup;
    }

    tuple->first = (int64_t)first;
    tuple->second = (int64_t)second;
    success = 1;

cleanup:
    free(line);
    return success;
}

int main(void)
{
    size_t count;
    Tuple *tuples = NULL;
    int64_t minimum;
    int status = EXIT_FAILURE;

    if (!read_size(&count) || count > SIZE_MAX / sizeof(*tuples)) {
        fputs("Invalid tuple count\n", stderr);
        return EXIT_FAILURE;
    }

    tuples = malloc(count * sizeof(*tuples));
    if (tuples == NULL) {
        fputs("Memory allocation failed\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < count; ++i) {
        if (!read_tuple(&tuples[i])) {
            fputs("Invalid tuple input\n", stderr);
            goto cleanup;
        }
    }

    if (!minimum_tuple_product(tuples, count, &minimum)) {
        fputs("Unable to calculate product safely\n", stderr);
        goto cleanup;
    }

    if (printf("%" PRId64 "\n", minimum) < 0) {
        fputs("Output error\n", stderr);
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free(tuples);
    return status;
}