#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int read_line(char **line, size_t *capacity)
{
    size_t length = 0;
    int ch = EOF;

    if (line == NULL || capacity == NULL) {
        return 0;
    }

    if (*line == NULL || *capacity < 2) {
        char *new_line;
        size_t new_capacity = 64;

        new_line = realloc(*line, new_capacity);
        if (new_line == NULL) {
            return 0;
        }

        *line = new_line;
        *capacity = new_capacity;
    }

    for (;;) {
        ch = fgetc(stdin);

        if (ch == '\n' || ch == EOF) {
            break;
        }

        if (length > SIZE_MAX - 2) {
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
                new_capacity = required;
            }

            new_line = realloc(*line, new_capacity);
            if (new_line == NULL) {
                return 0;
            }

            *line = new_line;
            *capacity = new_capacity;
        }

        (*line)[length++] = (char)(unsigned char)ch;
    }

    if (ferror(stdin)) {
        return 0;
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

    while (*text != '\0' && isspace((unsigned char)*text)) {
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
    const char *start;
    char *end;
    uintmax_t parsed;

    if (text == NULL || length == NULL) {
        return 0;
    }

    start = text;
    while (*start != '\0' && isspace((unsigned char)*start)) {
        ++start;
    }

    if (*start == '-' || *start == '\0') {
        return 0;
    }

    errno = 0;
    parsed = strtoumax(start, &end, 10);

    if (end == start || errno == ERANGE || parsed == 0 ||
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

    if (a == 0 || b == 0) {
        *result = 0;
        return 1;
    }

    if (a == -1) {
        if (b == INT64_MIN) {
            return 0;
        }
    } else if (b == -1) {
        if (a == INT64_MIN) {
            return 0;
        }
    } else if (a > 0) {
        if (b > 0) {
            if (a > INT64_MAX / b) {
                return 0;
            }
        } else if (b < INT64_MIN / a) {
            return 0;
        }
    } else {
        if (b > 0) {
            if (a < INT64_MIN / b) {
                return 0;
            }
        } else if (a < INT64_MAX / b) {
            return 0;
        }
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
    size_t length = 0;
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

    if (!maximum_increasing_subsequence_product(values, length, &maximum)) {
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