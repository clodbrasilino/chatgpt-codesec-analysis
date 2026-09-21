#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int cube_elements(const int64_t *input, int64_t *output, size_t count)
{
    const int64_t max_root = INT64_C(2097151);
    const int64_t min_root = -INT64_C(2097152);

    if (count != 0 && (input == NULL || output == NULL)) {
        return -1;
    }

    for (size_t i = 0; i < count; ++i) {
        if (input[i] < min_root || input[i] > max_root) {
            return -1;
        }

        output[i] = input[i] * input[i] * input[i];
    }

    return 0;
}

static int read_line(char **line, size_t *capacity)
{
    ssize_t length;

    if (line == NULL || capacity == NULL) {
        return -1;
    }

    errno = 0;
    length = getline(line, capacity, stdin);

    if (length < 0) {
        return -1;
    }

    if (length == 0 || (*line)[length - 1] != '\n') {
        int ch;

        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
        }

        return -1;
    }

    return 0;
}

static int read_size(size_t *value)
{
    char *line = NULL;
    char *end;
    size_t capacity = 0;
    uintmax_t parsed;
    int result = -1;

    if (value == NULL || read_line(&line, &capacity) != 0) {
        free(line);
        return -1;
    }

    if (line[0] == '-') {
        free(line);
        return -1;
    }

    errno = 0;
    parsed = strtoumax(line, &end, 10);

    if (end != line && errno != ERANGE && parsed <= SIZE_MAX) {
        while (*end == ' ' || *end == '\t' || *end == '\r') {
            ++end;
        }

        if (*end == '\n' && end[1] == '\0') {
            *value = (size_t)parsed;
            result = 0;
        }
    }

    free(line);
    return result;
}

static int read_int64(int64_t *value)
{
    char *line = NULL;
    char *end;
    size_t capacity = 0;
    intmax_t parsed;
    int result = -1;

    if (value == NULL || read_line(&line, &capacity) != 0) {
        free(line);
        return -1;
    }

    errno = 0;
    parsed = strtoimax(line, &end, 10);

    if (end != line && errno != ERANGE &&
        parsed >= INT64_MIN && parsed <= INT64_MAX) {
        while (*end == ' ' || *end == '\t' || *end == '\r') {
            ++end;
        }

        if (*end == '\n' && end[1] == '\0') {
            *value = (int64_t)parsed;
            result = 0;
        }
    }

    free(line);
    return result;
}

int main(void)
{
    size_t count;
    int64_t *values = NULL;
    int64_t *cubes = NULL;
    int status = EXIT_FAILURE;

    if (read_size(&count) != 0) {
        fputs("Failed to read the element count.\n", stderr);
        goto cleanup;
    }

    if (count > SIZE_MAX / sizeof(*values)) {
        fputs("Element count is too large.\n", stderr);
        goto cleanup;
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
    free(values);
    free(cubes);
    return status;
}