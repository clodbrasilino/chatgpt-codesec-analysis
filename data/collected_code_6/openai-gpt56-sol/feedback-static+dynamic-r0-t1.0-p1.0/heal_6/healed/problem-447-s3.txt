#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int cube_elements(const intmax_t *input, intmax_t *output, size_t count)
{
    if (count != 0 && (input == NULL || output == NULL)) {
        return -1;
    }

    for (size_t i = 0; i < count; ++i) {
        const intmax_t value = input[i];

        if (value > 0) {
            if (value > INTMAX_MAX / value) {
                return -1;
            }

            const intmax_t square = value * value;

            if (square > INTMAX_MAX / value) {
                return -1;
            }

            output[i] = square * value;
        } else if (value < 0) {
            if (value < INTMAX_MIN / value) {
                return -1;
            }

            const intmax_t square = value * value;

            if (square > INTMAX_MIN / value) {
                return -1;
            }

            output[i] = square * value;
        } else {
            output[i] = 0;
        }
    }

    return 0;
}

static int read_line(char **line)
{
    if (line == NULL) {
        return -1;
    }

    *line = NULL;

    size_t length = 0;
    size_t capacity = 64;
    char *buffer = malloc(capacity);

    if (buffer == NULL) {
        return -1;
    }

    for (;;) {
        int ch = fgetc(stdin);

        if (ch == EOF) {
            if (ferror(stdin) || length == 0) {
                free(buffer);
                return -1;
            }
            break;
        }

        if (ch == '\n') {
            break;
        }

        if (length >= capacity - 1) {
            if (capacity > SIZE_MAX / 2) {
                free(buffer);
                return -1;
            }

            const size_t new_capacity = capacity * 2;
            char *resized = realloc(buffer, new_capacity);

            if (resized == NULL) {
                free(buffer);
                return -1;
            }

            buffer = resized;
            capacity = new_capacity;
        }

        buffer[length++] = (char)(unsigned char)ch;
    }

    buffer[length] = '\0';
    *line = buffer;
    return 0;
}

static int is_horizontal_space(char ch)
{
    return ch == ' ' || ch == '\t' || ch == '\r';
}

static int read_size(size_t *value)
{
    if (value == NULL) {
        return -1;
    }

    char *buffer = NULL;

    if (read_line(&buffer) != 0) {
        return -1;
    }

    char *cursor = buffer;

    while (is_horizontal_space(*cursor)) {
        ++cursor;
    }

    if (*cursor == '-' || *cursor == '+' || *cursor == '\0') {
        free(buffer);
        return -1;
    }

    errno = 0;
    char *end = NULL;
    const uintmax_t parsed = strtoumax(cursor, &end, 10);

    if (end == cursor || errno == ERANGE || parsed > SIZE_MAX) {
        free(buffer);
        return -1;
    }

    while (is_horizontal_space(*end)) {
        ++end;
    }

    if (*end != '\0') {
        free(buffer);
        return -1;
    }

    *value = (size_t)parsed;
    free(buffer);
    return 0;
}

static int read_intmax(intmax_t *value)
{
    if (value == NULL) {
        return -1;
    }

    for (;;) {
        char *buffer = NULL;

        if (read_line(&buffer) != 0) {
            return -1;
        }

        char *cursor = buffer;

        while (is_horizontal_space(*cursor)) {
            ++cursor;
        }

        if (*cursor == '\0') {
            free(buffer);
            continue;
        }

        errno = 0;
        char *end = NULL;
        const intmax_t parsed = strtoimax(cursor, &end, 10);

        if (end == cursor || errno == ERANGE) {
            free(buffer);
            return -1;
        }

        while (is_horizontal_space(*end)) {
            ++end;
        }

        if (*end != '\0') {
            free(buffer);
            return -1;
        }

        *value = parsed;
        free(buffer);
        return 0;
    }
}

int main(void)
{
    size_t count = 0;
    intmax_t *values = NULL;
    intmax_t *cubes = NULL;

    if (read_size(&count) != 0) {
        fputs("Invalid element count\n", stderr);
        return EXIT_FAILURE;
    }

    if (count > SIZE_MAX / sizeof(*values)) {
        fputs("Element count is too large\n", stderr);
        return EXIT_FAILURE;
    }

    if (count != 0) {
        values = malloc(count * sizeof(*values));
        cubes = malloc(count * sizeof(*cubes));

        if (values == NULL || cubes == NULL) {
            fputs("Memory allocation failed\n", stderr);
            free(cubes);
            free(values);
            return EXIT_FAILURE;
        }
    }

    for (size_t i = 0; i < count; ++i) {
        if (read_intmax(&values[i]) != 0) {
            fputs("Invalid element\n", stderr);
            free(cubes);
            free(values);
            return EXIT_FAILURE;
        }
    }

    if (cube_elements(values, cubes, count) != 0) {
        fputs("Cube calculation overflow\n", stderr);
        free(cubes);
        free(values);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < count; ++i) {
        const char separator = i + 1 == count ? '\n' : ' ';

        if (printf("%" PRIdMAX "%c", cubes[i], separator) < 0) {
            free(cubes);
            free(values);
            return EXIT_FAILURE;
        }
    }

    free(cubes);
    free(values);
    return EXIT_SUCCESS;
}