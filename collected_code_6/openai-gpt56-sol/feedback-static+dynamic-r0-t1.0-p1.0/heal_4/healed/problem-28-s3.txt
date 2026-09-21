#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int binomial_coefficient(uint32_t n, uint32_t k, uint64_t *result)
{
    uint64_t value = 1;

    if (result == NULL || k > n) {
        return 0;
    }

    if (k > n - k) {
        k = n - k;
    }

    for (uint32_t i = 1; i <= k; ++i) {
        uint64_t factor = (uint64_t)(n - k + i);

        if (value > UINT64_MAX / factor) {
            return 0;
        }

        value *= factor;
        value /= i;
    }

    *result = value;
    return 1;
}

static int read_values(uint32_t *n, uint32_t *k)
{
    uintmax_t values[2];
    size_t count = 0;
    int ch = fgetc(stdin);

    if (n == NULL || k == NULL) {
        return 0;
    }

    while (ch != '\n' && ch != EOF) {
        uintmax_t value = 0;

        while (ch != '\n' && ch != EOF && isspace((unsigned char)ch)) {
            ch = fgetc(stdin);
        }

        if (ch == '\n' || ch == EOF) {
            break;
        }

        if (count >= 2 || ch == '-' || ch == '+') {
            do {
                ch = fgetc(stdin);
            } while (ch != '\n' && ch != EOF);
            return 0;
        }

        if (!isdigit((unsigned char)ch)) {
            do {
                ch = fgetc(stdin);
            } while (ch != '\n' && ch != EOF);
            return 0;
        }

        errno = 0;

        do {
            unsigned int digit = (unsigned int)(ch - '0');

            if (value > (UINT32_MAX - digit) / 10U) {
                errno = ERANGE;
            } else if (errno != ERANGE) {
                value = value * 10U + digit;
            }

            ch = fgetc(stdin);
        } while (ch != '\n' && ch != EOF && isdigit((unsigned char)ch));

        if (errno == ERANGE) {
            do {
                ch = fgetc(stdin);
            } while (ch != '\n' && ch != EOF);
            return 0;
        }

        if (ch != '\n' && ch != EOF && !isspace((unsigned char)ch)) {
            do {
                ch = fgetc(stdin);
            } while (ch != '\n' && ch != EOF);
            return 0;
        }

        values[count++] = value;
    }

    if (count != 2) {
        return 0;
    }

    *n = (uint32_t)values[0];
    *k = (uint32_t)values[1];
    return 1;
}

int main(void)
{
    uint32_t n;
    uint32_t k;
    uint64_t result;

    if (fputs("Enter n and k: ", stdout) == EOF || fflush(stdout) == EOF) {
        return EXIT_FAILURE;
    }

    if (!read_values(&n, &k)) {
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (!binomial_coefficient(n, k, &result)) {
        fputs("Invalid arguments or arithmetic overflow.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}