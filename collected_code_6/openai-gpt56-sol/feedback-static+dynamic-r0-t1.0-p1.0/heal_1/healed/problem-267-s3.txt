#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>
#include <ctype.h>

static int sum_odd_squares(uint64_t n, uint64_t *result)
{
    if (result == NULL || n > UINT64_C(1903309)) {
        return 0;
    }

    *result = n * (UINT64_C(2) * n - UINT64_C(1)) *
              (UINT64_C(2) * n + UINT64_C(1)) / UINT64_C(3);
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

    errno = 0;
    end = input;
    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end == '\0' || *end == '-') {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    {
        char *number_end;

        value = strtoumax(end, &number_end, 10);
        if (errno == ERANGE || number_end == end || value > UINT64_MAX) {
            fputs("Invalid input\n", stderr);
            return EXIT_FAILURE;
        }

        end = number_end;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    n = (uint64_t)value;

    if (!sum_odd_squares(n, &result)) {
        fputs("Input is too large\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", result);
    return EXIT_SUCCESS;
}