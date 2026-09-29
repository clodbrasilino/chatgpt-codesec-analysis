#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int read_line(char **line, size_t *capacity)
{
    size_t length = 0;
    int ch;

    if (line == NULL || capacity == NULL) {
        return 0;
    }

    if (*line == NULL || *capacity == 0) {
        *capacity = 64;
        *line = malloc(*capacity);
        if (*line == NULL) {
            return 0;
        }
    }

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
        if (length + 1 >= *capacity) {
            size_t new_capacity;
            char *new_line;

            if (*capacity > SIZE_MAX / 2) {
                return 0;
            }

            new_capacity = *capacity * 2;
            new_line = realloc(*line, new_capacity);
            if (new_line == NULL) {
                return 0;
            }

            *line = new_line;
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

static int trailing_input_is_valid(const char *text)
{
    if (text == NULL) {
        return 0;
    }

    while (*text == ' ' || *text == '\t' || *text == '\r') {
        ++text;
    }

    return *text == '\0';
}

static int parse_int64(const char *text, int64_t *value)
{
    char *end;
    intmax_t parsed;

    if (text == NULL || value == NULL) {
        return 0;
    }

    errno = 0;
    end = NULL;
    parsed = strtoimax(text, &end, 10);

    if (end == text || errno == ERANGE ||
        parsed < INT64_MIN || parsed > INT64_MAX ||
        !trailing_input_is_valid(end)) {
        return 0;
    }

    *value = (int64_t)parsed;
    return 1;
}

static int parse_length(const char *text, size_t *length)
{
    char *end;
    uintmax_t parsed;

    if (text == NULL || length == NULL || *text == '-') {
        return 0;
    }

    errno = 0;
    end = NULL;
    parsed = strtoumax(text, &end, 10);

    if (end == text || errno == ERANGE || parsed == 0 ||
        parsed > SIZE_MAX || !trailing_input_is_valid(end)) {
        return 0;
    }

    *length = (size_t)parsed;
    return 1;
}

static int multiply_checked(int64_t a, int64_t b, int64_t *result)
{
    if (result == NULL) {
        return 0;
    }

    if ((a > 0 && b > 0 && a > INT64_MAX / b) ||
        (a > 0 && b < 0 && b < INT64_MIN / a) ||
        (a < 0 && b > 0 && a < INT64_MIN / b) ||
        (a < 0 && b < 0 && a < INT64_MAX / b)) {
        return 0;
    }

    *result = a * b;
    return 1;
}

static int maximum_increasing_subsequence_product(
    const int64_t *values,
    size_t length,
    int64_t *maximum)
{
    int64_t *products;
    int64_t best;
    size_t i;

    if (values == NULL || maximum == NULL || length == 0 ||
        length > SIZE_MAX / sizeof(*products)) {
        return 0;
    }

    products = malloc(length * sizeof(*products));
    if (products == NULL) {
        return 0;
    }

    best = values[0];

    for (i = 0; i < length; ++i) {
        size_t j;

        products[i] = values[i];

        for (j = 0; j < i; ++j) {
            int64_t candidate;

            if (values[j] < values[i] &&
                multiply_checked(products[j], values[i], &candidate) &&
                candidate > products[i]) {
                products[i] = candidate;
            }
        }

        if (products[i] > best) {
            best = products[i];
        }
    }

    free(products);
    *maximum = best;
    return 1;
}

int main(void)
{
    char *line = NULL;
    size_t line_capacity = 0;
    size_t length;
    int64_t *values = NULL;
    int64_t maximum;
    size_t i;
    int status = EXIT_FAILURE;

    if (!read_line(&line, &line_capacity) ||
        !parse_length(line, &length) ||
        length > SIZE_MAX / sizeof(*values)) {
        fputs("Invalid input\n", stderr);
        goto cleanup;
    }

    values = malloc(length * sizeof(*values));
    if (values == NULL) {
        perror("malloc");
        goto cleanup;
    }

    for (i = 0; i < length; ++i) {
        if (!read_line(&line, &line_capacity) ||
            !parse_int64(line, &values[i])) {
            fputs("Invalid input\n", stderr);
            goto cleanup;
        }
    }

    if (!maximum_increasing_subsequence_product(
            values, length, &maximum)) {
        fputs("Unable to calculate result\n", stderr);
        goto cleanup;
    }

    if (printf("%" PRId64 "\n", maximum) < 0) {
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free(values);
    free(line);
    return status;
}