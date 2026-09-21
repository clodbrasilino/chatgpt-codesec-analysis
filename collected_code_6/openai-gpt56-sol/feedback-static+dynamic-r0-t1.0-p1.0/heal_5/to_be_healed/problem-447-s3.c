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
        intmax_t value = input[i];

        if (value > 0) {
            if (value > INTMAX_MAX / value) {
                return -1;
            }

            intmax_t square = value * value;

            if (square > INTMAX_MAX / value) {
                return -1;
            }

            output[i] = square * value;
        } else if (value < 0) {
            if (value < INTMAX_MIN / value) {
                return -1;
            }

            intmax_t square = value * value;

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

static int read_size(size_t *value)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[128];
    char *end;
    uintmax_t parsed;

    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return -1;
    }

    errno = 0;
    parsed = strtoumax(buffer, &end, 10);

    if (end == buffer || errno == ERANGE || parsed > SIZE_MAX) {
        return -1;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r') {
        ++end;
    }

    if (*end != '\n' && *end != '\0') {
        return -1;
    }

    *value = (size_t)parsed;
    return 0;
}

static int read_intmax(intmax_t *value)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[256];
    /* Possible weaknesses found:
     *  The scope of the variable 'cursor' can be reduced. [variableScope]
     */
    char *cursor;
    char *end;
    intmax_t parsed;

    for (;;) {
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            return -1;
        }

        cursor = buffer;

        while (*cursor == ' ' || *cursor == '\t' || *cursor == '\r' ||
               *cursor == '\n') {
            ++cursor;
        }

        if (*cursor == '\0') {
            continue;
        }

        errno = 0;
        parsed = strtoimax(cursor, &end, 10);

        if (end == cursor || errno == ERANGE) {
            return -1;
        }

        while (*end == ' ' || *end == '\t' || *end == '\r') {
            ++end;
        }

        if (*end != '\n' && *end != '\0') {
            return -1;
        }

        *value = parsed;
        return 0;
    }
}

int main(void)
{
    size_t count;
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
        char separator = i + 1 == count ? '\n' : ' ';

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