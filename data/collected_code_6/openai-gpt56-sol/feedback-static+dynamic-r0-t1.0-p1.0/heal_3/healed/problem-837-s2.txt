#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int cube_sum_first_n_odds(uint64_t n, uint64_t *result)
{
    uint64_t square;

    if (result == NULL || n > UINT64_C(55108)) {
        return 0;
    }

    square = n * n;
    *result = square * (UINT64_C(2) * square - UINT64_C(1));
    return 1;
}

static int read_input(char *buffer, size_t size)
{
    size_t length;
    int ch;

    if (buffer == NULL || size < 2 || fgets(buffer, size, stdin) == NULL) {
        return 0;
    }

    for (length = 0; length < size && buffer[length] != '\0'; ++length) {
        if (buffer[length] == '\n') {
            return 1;
        }
    }

    if (length == size) {
        return 0;
    }

    if (feof(stdin)) {
        return 1;
    }

    do {
        ch = fgetc(stdin);
    } while (ch != '\n' && ch != EOF);

    return 0;
}

int main(void)
{
    char input[128];
    char *end;
    uintmax_t value;
    uint64_t result;

    if (!read_input(input, sizeof input)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    value = strtoumax(input, &end, 10);

    if (end == input || errno == ERANGE || value > UINT64_MAX) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r' ||
           *end == '\n' || *end == '\v' || *end == '\f') {
        ++end;
    }

    if (*end != '\0') {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (!cube_sum_first_n_odds((uint64_t)value, &result)) {
        fputs("Input is too large\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}