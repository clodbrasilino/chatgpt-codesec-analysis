#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int cube_sum_first_n_odds(uint64_t n, uint64_t *result)
{
    uint64_t n_squared;

    if (result == NULL || n > UINT64_C(77935)) {
        return 0;
    }

    n_squared = n * n;
    *result = n_squared * (UINT64_C(2) * n_squared - UINT64_C(1));
    return 1;
}

int main(void)
{
    char input[128];
    char *end;
    uintmax_t value;
    uint64_t n;
    uint64_t result;

    if (fgets(input, sizeof input, stdin) == NULL) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    {
        size_t length = 0;

        while (length < sizeof input && input[length] != '\0') {
            ++length;
        }

        if (length == sizeof input) {
            fputs("Invalid input\n", stderr);
            return EXIT_FAILURE;
        }

        if (length == 0 || input[length - 1] != '\n') {
            int ch = fgetc(stdin);

            if (ch != EOF) {
                while (ch != '\n' && ch != EOF) {
                    ch = fgetc(stdin);
                }

                fputs("Invalid input\n", stderr);
                return EXIT_FAILURE;
            }
        }
    }

    errno = 0;
    end = NULL;
    value = strtoumax(input, &end, 10);

    if (errno == ERANGE || end == input) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r' ||
           *end == '\n' || *end == '\f' || *end == '\v') {
        ++end;
    }

    if (*end != '\0' || value > UINT64_MAX) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    n = (uint64_t)value;

    if (!cube_sum_first_n_odds(n, &result)) {
        fputs("Input is too large\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}