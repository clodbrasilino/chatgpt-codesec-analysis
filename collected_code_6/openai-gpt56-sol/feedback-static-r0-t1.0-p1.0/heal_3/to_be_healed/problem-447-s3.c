#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int read_size(size_t *value)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[128];
    char *end = NULL;
    uintmax_t parsed;

    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return -1;
    }

    errno = 0;
    parsed = strtoumax(buffer, &end, 10);

    if (end == buffer || errno == ERANGE || parsed > SIZE_MAX) {
        return -1;
    }

    while (*end == ' ' || *end == '\t' || *end == '\n' ||
           *end == '\r' || *end == '\f' || *end == '\v') {
        ++end;
    }

    if (*end != '\0') {
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
    char buffer[128];
    char *end = NULL;
    intmax_t parsed;

    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return -1;
    }

    errno = 0;
    parsed = strtoimax(buffer, &end, 10);

    if (end == buffer || errno == ERANGE) {
        return -1;
    }

    while (*end == ' ' || *end == '\t' || *end == '\n' ||
           *end == '\r' || *end == '\f' || *end == '\v') {
        ++end;
    }

    if (*end != '\0') {
        return -1;
    }

    *value = parsed;
    return 0;
}

static int cube_elements(const intmax_t *input, intmax_t *output, size_t count)
{
    if (count != 0U && (input == NULL || output == NULL)) {
        return -1;
    }

    for (size_t i = 0U; i < count; ++i) {
        const intmax_t value = input[i];
        intmax_t square;

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

        output[i] = square * value;
    }

    return 0;
}

int main(void)
{
    size_t count = 0U;
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

    if (count != 0U) {
        values = malloc(count * sizeof(*values));
        cubes = malloc(count * sizeof(*cubes));

        if (values == NULL || cubes == NULL) {
            free(values);
            free(cubes);
            fputs("Memory allocation failed\n", stderr);
            return EXIT_FAILURE;
        }
    }

    for (size_t i = 0U; i < count; ++i) {
        if (read_intmax(&values[i]) != 0) {
            fputs("Invalid element\n", stderr);
            free(values);
            free(cubes);
            return EXIT_FAILURE;
        }
    }

    if (cube_elements(values, cubes, count) != 0) {
        fputs("Cube calculation overflow\n", stderr);
        free(values);
        free(cubes);
        return EXIT_FAILURE;
    }

    for (size_t i = 0U; i < count; ++i) {
        if (printf("%" PRIdMAX "%c", cubes[i],
                   i + 1U == count ? '\n' : ' ') < 0) {
            free(values);
            free(cubes);
            return EXIT_FAILURE;
        }
    }

    free(values);
    free(cubes);
    return EXIT_SUCCESS;
}