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

    *result = (n == 0U) ? UINT64_C(1) : (UINT64_C(1) << (n - 1U));
    return 0;
}

static int read_value(uint32_t *value)
{
    char input[64];
    char *end;
    unsigned long parsed;

    if (value == NULL || fgets(input, sizeof input, stdin) == NULL) {
        return -1;
    }

    char *newline = NULL;
    for (size_t i = 0; i < sizeof input; ++i) {
        if (input[i] == '\n') {
            newline = &input[i];
            break;
        }
        if (input[i] == '\0') {
            break;
        }
    }

    if (newline == NULL) {
        int ch = fgetc(stdin);

        if (ch != '\n' && ch != EOF) {
            do {
                ch = fgetc(stdin);
            } while (ch != '\n' && ch != EOF);
            return -1;
        }
    }

    errno = 0;
    end = input;
    parsed = strtoul(input, &end, 10);

    if (errno == ERANGE || end == input || parsed > 64UL) {
        return -1;
    }

    while (*end == ' ' || *end == '\t' || *end == '\n' ||
           *end == '\r' || *end == '\f' || *end == '\v') {
        ++end;
    }

    if (*end != '\0') {
        return -1;
    }

    *value = (uint32_t)parsed;
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