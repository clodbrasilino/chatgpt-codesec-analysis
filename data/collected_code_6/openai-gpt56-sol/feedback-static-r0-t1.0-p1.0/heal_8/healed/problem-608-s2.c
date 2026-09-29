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
    if (value == NULL) {
        return false;
    }

    enum { BUFFER_SIZE = 128 };
    char buffer[BUFFER_SIZE];

    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return false;
    }

    size_t length = 0U;
    while (length < sizeof(buffer) && buffer[length] != '\0' &&
           buffer[length] != '\n') {
        ++length;
    }

    if (length == sizeof(buffer)) {
        return false;
    }

    if (buffer[length] == '\n') {
        buffer[length] = '\0';
    } else if (!feof(stdin)) {
        int ch;
        do {
            ch = fgetc(stdin);
        } while (ch != '\n' && ch != EOF);

        return false;
    }

    errno = 0;
    char *end = NULL;
    uintmax_t parsed = strtoumax(buffer, &end, 10);

    if (end == buffer || errno == ERANGE) {
        return false;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r' ||
           *end == '\f' || *end == '\v') {
        ++end;
    }

    if (*end != '\0' || parsed > SIZE_MAX) {
        return false;
    }

    *value = parsed;
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