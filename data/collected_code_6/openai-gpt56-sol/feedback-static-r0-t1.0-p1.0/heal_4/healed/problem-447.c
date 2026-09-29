#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int read_line(char **line)
{
    size_t length = 0;
    size_t capacity = 64;
    char *buffer;
    int ch;

    if (line == NULL) {
        return -1;
    }

    *line = NULL;
    buffer = malloc(capacity);

    if (buffer == NULL) {
        return -1;
    }

    for (;;) {
        ch = fgetc(stdin);

        if (ch == EOF || ch == '\n') {
            break;
        }

        if (length == capacity - 1) {
            size_t new_capacity;
            char *new_buffer;

            if (capacity > SIZE_MAX / 2) {
                free(buffer);
                return -1;
            }

            new_capacity = capacity * 2;
            new_buffer = realloc(buffer, new_capacity);

            if (new_buffer == NULL) {
                free(buffer);
                return -1;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        buffer[length++] = (char)ch;
    }

    if (ch == EOF) {
        if (ferror(stdin) || length == 0) {
            free(buffer);
            return -1;
        }
    }

    buffer[length] = '\0';
    *line = buffer;
    return 0;
}

static int only_trailing_space(const char *text)
{
    if (text == NULL) {
        return 0;
    }

    while (*text == ' ' ||
           *text == '\t' ||
           *text == '\r' ||
           *text == '\v' ||
           *text == '\f') {
        ++text;
    }

    return *text == '\0';
}

static int read_size(size_t *value)
{
    char *line = NULL;
    char *end = NULL;
    uintmax_t parsed;
    int result = -1;

    if (value == NULL || read_line(&line) != 0) {
        return -1;
    }

    errno = 0;
    parsed = strtoumax(line, &end, 10);

    if (end != line &&
        errno != ERANGE &&
        parsed <= SIZE_MAX &&
        line[0] != '-' &&
        only_trailing_space(end)) {
        *value = (size_t)parsed;
        result = 0;
    }

    free(line);
    return result;
}

static int read_int64(int64_t *value)
{
    char *line = NULL;
    char *end = NULL;
    intmax_t parsed;
    int result = -1;

    if (value == NULL || read_line(&line) != 0) {
        return -1;
    }

    errno = 0;
    parsed = strtoimax(line, &end, 10);

    if (end != line &&
        errno != ERANGE &&
        parsed >= INT64_MIN &&
        parsed <= INT64_MAX &&
        only_trailing_space(end)) {
        *value = (int64_t)parsed;
        result = 0;
    }

    free(line);
    return result;
}

static int cube_elements(const int64_t *input, int64_t *output, size_t count)
{
    const int64_t minimum_root = -INT64_C(2097152);
    const int64_t maximum_root = INT64_C(2097151);

    if (count != 0 && (input == NULL || output == NULL)) {
        return -1;
    }

    for (size_t i = 0; i < count; ++i) {
        int64_t value = input[i];

        if (value < minimum_root || value > maximum_root) {
            return -1;
        }

        output[i] = value * value * value;
    }

    return 0;
}

int main(void)
{
    size_t count;
    int64_t *values = NULL;
    int64_t *cubes = NULL;
    int status = EXIT_FAILURE;

    if (read_size(&count) != 0) {
        fputs("Failed to read the element count.\n", stderr);
        return EXIT_FAILURE;
    }

    if (count > SIZE_MAX / sizeof(*values)) {
        fputs("Element count is too large.\n", stderr);
        return EXIT_FAILURE;
    }

    if (count != 0) {
        values = malloc(count * sizeof(*values));
        cubes = malloc(count * sizeof(*cubes));

        if (values == NULL || cubes == NULL) {
            fputs("Memory allocation failed.\n", stderr);
            goto cleanup;
        }
    }

    for (size_t i = 0; i < count; ++i) {
        if (read_int64(&values[i]) != 0) {
            fputs("Failed to read an element.\n", stderr);
            goto cleanup;
        }
    }

    if (cube_elements(values, cubes, count) != 0) {
        fputs("An element cannot be cubed without overflow.\n", stderr);
        goto cleanup;
    }

    for (size_t i = 0; i < count; ++i) {
        if (printf("%" PRId64 "%c",
                   cubes[i],
                   i + 1 == count ? '\n' : ' ') < 0) {
            fputs("Failed to write output.\n", stderr);
            goto cleanup;
        }
    }

    status = EXIT_SUCCESS;

cleanup:
    free(cubes);
    free(values);
    return status;
}