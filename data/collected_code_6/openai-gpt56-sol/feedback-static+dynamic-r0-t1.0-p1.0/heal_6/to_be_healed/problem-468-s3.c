#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

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

static int read_line(char **line)
{
    char *buffer;
    size_t capacity = 64;
    size_t length = 0;

    if (line == NULL) {
        return 0;
    }

    *line = NULL;
    buffer = malloc(capacity);

    if (buffer == NULL) {
        return 0;
    }

    for (;;) {
        int ch;

        if (length + 1 >= capacity) {
            char *resized;
            size_t new_capacity;

            if (capacity > SIZE_MAX / 2) {
                free(buffer);
                return 0;
            }

            new_capacity = capacity * 2;
            resized = realloc(buffer, new_capacity);

            if (resized == NULL) {
                free(buffer);
                return 0;
            }

            buffer = resized;
            capacity = new_capacity;
        }

        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);

        if (ch == '\n') {
            break;
        }

        if (ch == EOF) {
            if (ferror(stdin) || length == 0) {
                free(buffer);
                return 0;
            }
            break;
        }

        buffer[length++] = (char)ch;
    }

    buffer[length] = '\0';
    *line = buffer;
    return 1;
}

static int only_trailing_space(const char *text)
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
    char *line;
    char *end;
    uintmax_t parsed;
    int valid;

    if (value == NULL || !read_line(&line)) {
        return 0;
    }

    errno = 0;
    end = NULL;
    parsed = strtoumax(line, &end, 10);

    valid = errno != ERANGE &&
            end != line &&
            parsed != 0 &&
            parsed <= SIZE_MAX &&
            only_trailing_space(end);

    if (valid) {
        *value = (size_t)parsed;
    }

    free(line);
    return valid;
}

static int read_int64(int64_t *value)
{
    char *line;
    char *end;
    intmax_t parsed;
    int valid;

    if (value == NULL || !read_line(&line)) {
        return 0;
    }

    errno = 0;
    end = NULL;
    parsed = strtoimax(line, &end, 10);

    valid = errno != ERANGE &&
            end != line &&
            parsed >= INT64_MIN &&
            parsed <= INT64_MAX &&
            only_trailing_space(end);

    if (valid) {
        *value = (int64_t)parsed;
    }

    free(line);
    return valid;
}

int main(void)
{
    size_t length;
    int64_t *values;
    int64_t maximum;
    size_t i;

    if (!read_size(&length) ||
        length > SIZE_MAX / sizeof(*values)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    values = malloc(length * sizeof(*values));

    if (values == NULL) {
        perror("malloc");
        return EXIT_FAILURE;
    }

    for (i = 0; i < length; ++i) {
        if (!read_int64(&values[i])) {
            fputs("Invalid input\n", stderr);
            free(values);
            return EXIT_FAILURE;
        }
    }

    if (!maximum_increasing_subsequence_product(
            values, length, &maximum)) {
        fputs("Unable to calculate result\n", stderr);
        free(values);
        return EXIT_FAILURE;
    }

    if (printf("%" PRId64 "\n", maximum) < 0) {
        free(values);
        return EXIT_FAILURE;
    }

    free(values);
    return EXIT_SUCCESS;
}