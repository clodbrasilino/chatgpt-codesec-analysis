#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int read_line(char **line)
{
    size_t capacity = 64U;
    size_t length = 0U;
    char *buffer = malloc(capacity);

    if (buffer == NULL) {
        return -1;
    }

    for (;;) {
        int ch = fgetc(stdin);

        if (ch == EOF) {
            if (ferror(stdin) || length == 0U) {
                free(buffer);
                return -1;
            }
            break;
        }

        if (ch == '\n') {
            break;
        }

        if (length + 1U >= capacity) {
            size_t new_capacity;
            char *resized;

            if (capacity > SIZE_MAX / 2U) {
                free(buffer);
                return -1;
            }

            new_capacity = capacity * 2U;
            resized = realloc(buffer, new_capacity);
            if (resized == NULL) {
                free(buffer);
                return -1;
            }

            buffer = resized;
            capacity = new_capacity;
        }

        buffer[length++] = (char)ch;
    }

    buffer[length] = '\0';
    *line = buffer;
    return 0;
}

static int is_space_char(char ch)
{
    return ch == ' ' || ch == '\t' || ch == '\n' ||
           ch == '\r' || ch == '\f' || ch == '\v';
}

static int read_size(size_t *value)
{
    char *buffer = NULL;
    char *end;
    uintmax_t parsed;

    if (value == NULL || read_line(&buffer) != 0) {
        return -1;
    }

    errno = 0;
    parsed = strtoumax(buffer, &end, 10);

    if (end == buffer || errno == ERANGE || parsed > SIZE_MAX) {
        free(buffer);
        return -1;
    }

    while (is_space_char(*end)) {
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
    char *buffer = NULL;
    char *end;
    intmax_t parsed;

    if (value == NULL || read_line(&buffer) != 0) {
        return -1;
    }

    errno = 0;
    parsed = strtoimax(buffer, &end, 10);

    if (end == buffer || errno == ERANGE) {
        free(buffer);
        return -1;
    }

    while (is_space_char(*end)) {
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

static int cube_value(intmax_t value, intmax_t *result)
{
    intmax_t square;

    if (result == NULL) {
        return -1;
    }

    if (value != 0 &&
        ((value > 0 && value > INTMAX_MAX / value) ||
         (value < 0 && value < INTMAX_MAX / value))) {
        return -1;
    }

    square = value * value;

    if ((value > 0 && square > INTMAX_MAX / value) ||
        (value < 0 && square > INTMAX_MIN / value)) {
        return -1;
    }

    *result = square * value;
    return 0;
}

static int cube_elements(const intmax_t *input, intmax_t *output, size_t count)
{
    if (count != 0U && (input == NULL || output == NULL)) {
        return -1;
    }

    for (size_t i = 0U; i < count; ++i) {
        if (cube_value(input[i], &output[i]) != 0) {
            return -1;
        }
    }

    return 0;
}

int main(void)
{
    size_t count;
    intmax_t *values = NULL;
    intmax_t *cubes = NULL;
    int status = EXIT_FAILURE;

    if (read_size(&count) != 0) {
        fputs("Invalid element count\n", stderr);
        return EXIT_FAILURE;
    }

    if (count > SIZE_MAX / sizeof(*values)) {
        fputs("Element count is too large\n", stderr);
        return EXIT_FAILURE;
    }

    if (count != 0U) {
        values = malloc(count * sizeof(*values));
        cubes = malloc(count * sizeof(*cubes));

        if (values == NULL || cubes == NULL) {
            fputs("Memory allocation failed\n", stderr);
            goto cleanup;
        }
    }

    for (size_t i = 0U; i < count; ++i) {
        if (read_intmax(&values[i]) != 0) {
            fputs("Invalid element\n", stderr);
            goto cleanup;
        }
    }

    if (cube_elements(values, cubes, count) != 0) {
        fputs("Cube calculation overflow\n", stderr);
        goto cleanup;
    }

    for (size_t i = 0U; i < count; ++i) {
        if (printf("%" PRIdMAX "%c", cubes[i],
                   i + 1U == count ? '\n' : ' ') < 0) {
            goto cleanup;
        }
    }

    status = EXIT_SUCCESS;

cleanup:
    free(values);
    free(cubes);
    return status;
}