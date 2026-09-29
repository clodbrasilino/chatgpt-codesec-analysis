#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static uintmax_t magnitude(intmax_t value)
{
    if (value < 0) {
        return (uintmax_t)(-(value + 1)) + UINTMAX_C(1);
    }

    return (uintmax_t)value;
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
    size_t length = 0;
    size_t capacity = 128;
    char *buffer = malloc(capacity);

    if (buffer == NULL) {
        *line = NULL;
        return 0;
    }

    for (;;) {
        int ch = fgetc(stdin);

        if (ch == '\n') {
            break;
        }

        if (ch == EOF) {
            if (ferror(stdin) || length == 0) {
                free(buffer);
                *line = NULL;
                return 0;
            }
            break;
        }

        if (length == SIZE_MAX - 1) {
            free(buffer);
            *line = NULL;
            return 0;
        }

        if (length + 1 >= capacity) {
            size_t new_capacity;

            if (capacity > SIZE_MAX / 2) {
                new_capacity = SIZE_MAX;
            } else {
                new_capacity = capacity * 2;
            }

            if (new_capacity <= capacity) {
                free(buffer);
                *line = NULL;
                return 0;
            }

            char *resized = realloc(buffer, new_capacity);
            if (resized == NULL) {
                free(buffer);
                *line = NULL;
                return 0;
            }

            buffer = resized;
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

    if (!read_line(&line)) {
        return 0;
    }

    char *end = NULL;
    errno = 0;
    intmax_t parsed = strtoimax(line, &end, 10);

    int valid = end != line &&
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

    if (!read_line(&line)) {
        return 0;
    }

    char *start = line;

    while (isspace((unsigned char)*start)) {
        ++start;
    }

    if (*start == '-') {
        free(line);
        return 0;
    }

    char *end = NULL;
    errno = 0;
    uintmax_t parsed = strtoumax(start, &end, 10);

    int valid = end != start &&
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

    if (!read_size(&count)) {
        fputs("Invalid array size\n", stderr);
        return EXIT_FAILURE;
    }

    intmax_t *values = malloc(count * sizeof(*values));

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

    uintmax_t result = gcd_array(values, count);
    free(values);

    if (printf("%" PRIuMAX "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}