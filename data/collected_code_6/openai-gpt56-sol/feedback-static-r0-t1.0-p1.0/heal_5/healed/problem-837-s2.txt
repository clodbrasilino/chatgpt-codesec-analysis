#include <ctype.h>
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

static int read_uint64(uint64_t *value)
{
    char input[128];
    char *end;
    uintmax_t parsed;

    if (value == NULL || fgets(input, sizeof input, stdin) == NULL) {
        return 0;
    }

    for (size_t i = 0; input[i] != '\0'; ++i) {
        if (input[i] == '\n') {
            input[i] = '\0';
            goto parse;
        }
    }

    if (!feof(stdin)) {
        int ch;

        do {
            ch = getchar();
        } while (ch != '\n' && ch != EOF);

        return 0;
    }

parse:
    errno = 0;
    parsed = strtoumax(input, &end, 10);

    if (errno == ERANGE || end == input || parsed > UINT64_MAX) {
        return 0;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        return 0;
    }

    *value = (uint64_t)parsed;
    return 1;
}

int main(void)
{
    uint64_t value;
    uint64_t result;

    if (!read_uint64(&value)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (!cube_sum_first_n_odds(value, &result)) {
        fputs("Input is too large\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}