#include <errno.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static bool nth_bell_number(size_t n, uint64_t *result)
{
    if (result == NULL || n > SIZE_MAX / sizeof(uint64_t) - 1U) {
        return false;
    }

    uint64_t *row = calloc(n + 1U, sizeof(*row));
    if (row == NULL) {
        return false;
    }

    row[0] = UINT64_C(1);

    for (size_t i = 1U; i <= n; ++i) {
        row[i] = row[0];

        for (size_t j = i; j > 0U; --j) {
            if (row[j - 1U] > UINT64_MAX - row[j]) {
                free(row);
                return false;
            }

            row[j - 1U] += row[j];
        }
    }

    *result = row[0];
    free(row);
    return true;
}

static bool read_input(uintmax_t *value)
{
    char *line = NULL;
    size_t capacity = 0U;
    size_t length = 0U;
    int ch;

    if (value == NULL) {
        return false;
    }

    while ((ch = getchar()) != '\n' && ch != EOF) {
        if (length == capacity) {
            size_t new_capacity;
            char *new_line;

            if (capacity == 0U) {
                new_capacity = 32U;
            } else {
                if (capacity > SIZE_MAX / 2U) {
                    free(line);
                    return false;
                }
                new_capacity = capacity * 2U;
            }

            new_line = realloc(line, new_capacity);
            if (new_line == NULL) {
                free(line);
                return false;
            }

            line = new_line;
            capacity = new_capacity;
        }

        line[length++] = (char)ch;
    }

    if (ch == EOF && ferror(stdin)) {
        free(line);
        return false;
    }

    if (length == 0U && ch == EOF) {
        free(line);
        return false;
    }

    if (length == SIZE_MAX) {
        free(line);
        return false;
    }

    if (length + 1U > capacity) {
        char *new_line = realloc(line, length + 1U);
        if (new_line == NULL) {
            free(line);
            return false;
        }
        line = new_line;
    }

    line[length] = '\0';

    errno = 0;
    char *end = NULL;
    uintmax_t parsed = strtoumax(line, &end, 10);

    if (end == line || errno == ERANGE) {
        free(line);
        return false;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r' ||
           *end == '\f' || *end == '\v') {
        ++end;
    }

    if (*end != '\0' || parsed > SIZE_MAX) {
        free(line);
        return false;
    }

    *value = parsed;
    free(line);
    return true;
}

int main(void)
{
    uintmax_t input;
    uint64_t result;

    if (!read_input(&input)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (!nth_bell_number((size_t)input, &result)) {
        fputs("Unable to compute Bell number\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}