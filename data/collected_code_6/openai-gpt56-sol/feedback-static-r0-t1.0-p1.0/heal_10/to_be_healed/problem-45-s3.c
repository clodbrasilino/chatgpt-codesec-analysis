#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static uintmax_t magnitude(intmax_t value)
{
    return value < 0
        ? (uintmax_t)(-(value + 1)) + UINTMAX_C(1)
        : (uintmax_t)value;
}

static uintmax_t gcd_pair(uintmax_t a, uintmax_t b)
{
    while (b != 0) {
        uintmax_t remainder = a % b;
        a = b;
        b = remainder;
    }

    return a;
}

static uintmax_t gcd_array(const intmax_t values[], size_t count)
{
    uintmax_t result = 0;

    for (size_t i = 0; i < count; ++i) {
        result = gcd_pair(result, magnitude(values[i]));
    }

    return result;
}

static int read_line(char **line)
{
    char *buffer = NULL;
    size_t length = 0;
    size_t capacity = 128;

    if (line == NULL) {
        return 0;
    }

    *line = NULL;
    buffer = malloc(capacity);

    if (buffer == NULL) {
        return 0;
    }

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int ch = getchar();

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

        if (length + 1 >= capacity) {
            size_t new_capacity;
            char *temporary;

            if (capacity > SIZE_MAX / 2) {
                free(buffer);
                return 0;
            }

            new_capacity = capacity * 2;
            temporary = realloc(buffer, new_capacity);

            if (temporary == NULL) {
                free(buffer);
                return 0;
            }

            buffer = temporary;
            capacity = new_capacity;
        }

        buffer[length++] = (char)(unsigned char)ch;
    }

    buffer[length] = '\0';
    *line = buffer;
    return 1;
}

static int only_whitespace(const char *text)
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

static int read_intmax(intmax_t *value)
{
    char *line = NULL;
    char *end = NULL;
    intmax_t parsed;
    int valid;

    if (value == NULL || !read_line(&line)) {
        return 0;
    }

    errno = 0;
    parsed = strtoimax(line, &end, 10);

    valid = end != line &&
            errno != ERANGE &&
            only_whitespace(end);

    if (valid) {
        *value = parsed;
    }

    free(line);
    return valid;
}

static int read_size(size_t *value)
{
    char *line = NULL;
    char *start;
    char *end = NULL;
    uintmax_t parsed;
    int valid;

    if (value == NULL || !read_line(&line)) {
        return 0;
    }

    start = line;

    while (isspace((unsigned char)*start)) {
        ++start;
    }

    if (*start == '+' || *start == '-' || *start == '\0') {
        free(line);
        return 0;
    }

    errno = 0;
    parsed = strtoumax(start, &end, 10);

    valid = end != start &&
            errno != ERANGE &&
            parsed != 0 &&
            parsed <= SIZE_MAX &&
            parsed <= SIZE_MAX / sizeof(intmax_t) &&
            only_whitespace(end);

    if (valid) {
        *value = (size_t)parsed;
    }

    free(line);
    return valid;
}

int main(void)
{
    size_t count;
    intmax_t *values;
    uintmax_t result;

    if (!read_size(&count)) {
        fputs("Invalid array size\n", stderr);
        return EXIT_FAILURE;
    }

    values = malloc(count * sizeof(*values));

    if (values == NULL) {
        fputs("Memory allocation failed\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < count; ++i) {
        if (!read_intmax(&values[i])) {
            fputs("Invalid array element\n", stderr);
            free(values);
            return EXIT_FAILURE;
        }
    }

    result = gcd_array(values, count);
    free(values);

    if (printf("%" PRIuMAX "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}