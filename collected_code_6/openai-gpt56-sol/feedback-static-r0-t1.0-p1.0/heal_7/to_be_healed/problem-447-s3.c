#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int read_line(char **line)
{
    size_t capacity = 64U;
    size_t length = 0U;
    char *buffer;

    if (line == NULL) {
        return -1;
    }

    *line = NULL;
    buffer = malloc(capacity);
    if (buffer == NULL) {
        return -1;
    }

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
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
    char *start;
    char *end;
    uintmax_t parsed;

    if (value == NULL || read_line(&buffer) != 0) {
        return -1;
    }

    start = buffer;
    while (is_space_char(*start)) {
        ++start;
    }

    if (*start == '-') {
        free(buffer);
        return -1;
    }

    errno = 0;
    parsed = strtoumax(start, &end, 10);

    if (end == start || errno == ERANGE || parsed > SIZE_MAX) {
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
    char *start;
    char *end;
    intmax_t parsed;

    if (value == NULL || read_line(&buffer) != 0) {
        return -1;
    }

    start = buffer;
    while (is_space_char(*start)) {
        ++start;
    }

    errno = 0;
    parsed = strtoimax(start, &end, 10);

    if (end == start || errno == ERANGE) {
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

static int multiply_intmax(intmax_t left, intmax_t right, intmax_t *result)
{
    if (result == NULL) {
        return -1;
    }

    if (left > 0) {
        if (right > 0) {
            if (left > INTMAX_MAX / right) {
                return -1;
            }
        } else if (right < 0) {
            if (right < INTMAX_MIN / left) {
                return -1;
            }
        }
    } else if (left < 0) {
        if (right > 0) {
            if (left < INTMAX_MIN / right) {
                return -1;
            }
        } else if (right < 0) {
            if (left < INTMAX_MAX / right) {
                return -1;
            }
        }
    }

    *result = left * right;
    return 0;
}

static int cube_value(intmax_t value, intmax_t *result)
{
    intmax_t square;

    if (result == NULL) {
        return -1;
    }

    if (multiply_intmax(value, value, &square) != 0) {
        return -1;
    }

    return multiply_intmax(square, value, result);
}

static int cube_elements(const intmax_t *input, intmax_t *output, size_t count)
{
    size_t i;

    if (count != 0U && (input == NULL || output == NULL)) {
        return -1;
    }

    for (i = 0U; i < count; ++i) {
        if (cube_value(input[i], &output[i]) != 0) {
            return -1;
        }
    }

    return 0;
}

int main(void)
{
    size_t count;
    size_t i;
    intmax_t *values = NULL;
    intmax_t *cubes = NULL;
    int status = EXIT_FAILURE;

    if (read_size(&count) != 0) {
        fputs("Invalid element count\n", stderr);
        return EXIT_FAILURE;
    }

    if (count > SIZE_MAX / sizeof(*values) ||
        count > SIZE_MAX / sizeof(*cubes)) {
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

    for (i = 0U; i < count; ++i) {
        if (read_intmax(&values[i]) != 0) {
            fputs("Invalid element\n", stderr);
            goto cleanup;
        }
    }

    if (cube_elements(values, cubes, count) != 0) {
        fputs("Cube calculation overflow\n", stderr);
        goto cleanup;
    }

    for (i = 0U; i < count; ++i) {
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