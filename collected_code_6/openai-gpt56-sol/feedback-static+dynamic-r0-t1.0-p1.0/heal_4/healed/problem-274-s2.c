#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int sum_even_index_binomial_coefficients(uint32_t n, uint64_t *result)
{
    if (result == NULL || n > 64U) {
        return -1;
    }

    *result = (n == 0U)
        ? UINT64_C(1)
        : (UINT64_C(1) << (n - 1U));

    return 0;
}

static int read_value(uint32_t *result)
{
    char input[128];
    char *end;
    unsigned long value;

    if (result == NULL || fgets(input, sizeof input, stdin) == NULL) {
        return -1;
    }

    end = input;
    while (*end != '\0' && *end != '\n') {
        ++end;
    }

    if (*end != '\n') {
        int ch;

        while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
        }

        return -1;
    }

    *end = '\0';

    errno = 0;
    end = NULL;
    value = strtoul(input, &end, 10);

    if (errno == ERANGE || end == input || value > UINT32_MAX) {
        return -1;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        return -1;
    }

    *result = (uint32_t)value;
    return 0;
}

int main(void)
{
    uint32_t value;
    uint64_t sum;

    if (read_value(&value) != 0) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (sum_even_index_binomial_coefficients(value, &sum) != 0) {
        fputs("Input is out of range\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", sum) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}