#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <ctype.h>
#include <errno.h>

static int sum_odd_squares(uint64_t n, uint64_t *result)
{
    if (result == NULL) {
        return 0;
    }

    if (n != 0 && n > UINT64_MAX / n) {
        return 0;
    }

    uint64_t n_squared = n * n;

    if (n_squared != 0 && n > UINT64_MAX / n_squared) {
        return 0;
    }

    uint64_t n_cubed = n_squared * n;

    if (n_cubed > (UINT64_MAX - n) / 4) {
        return 0;
    }

    *result = (4 * n_cubed - n) / 3;
    return 1;
}

int main(void)
{
    char input[128];
    char *end;
    uintmax_t value;
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

    char *number_end;
    value = strtoumax(end, &number_end, 10);

    if (errno == ERANGE || number_end == end || value > UINT64_MAX) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    while (isspace((unsigned char)*number_end)) {
        ++number_end;
    }

    if (*number_end != '\0') {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (!sum_odd_squares((uint64_t)value, &result)) {
        fputs("Result out of range\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", result);
    return EXIT_SUCCESS;
}