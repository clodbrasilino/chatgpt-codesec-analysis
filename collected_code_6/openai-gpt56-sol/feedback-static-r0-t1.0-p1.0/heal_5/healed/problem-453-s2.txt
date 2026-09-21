#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int is_space_char(char ch)
{
    return ch == ' ' || ch == '\t' || ch == '\n' ||
           ch == '\r' || ch == '\f' || ch == '\v';
}

static int sum_even_factors(uint64_t number, uint64_t *sum)
{
    uint64_t total = 0;

    if (number == 0 || sum == NULL) {
        return 0;
    }

    for (uint64_t divisor = 1; divisor <= number / divisor; ++divisor) {
        uint64_t quotient;

        if (number % divisor != 0) {
            continue;
        }

        quotient = number / divisor;

        if ((divisor & UINT64_C(1)) == 0) {
            if (total > UINT64_MAX - divisor) {
                return 0;
            }
            total += divisor;
        }

        if (quotient != divisor && (quotient & UINT64_C(1)) == 0) {
            if (total > UINT64_MAX - quotient) {
                return 0;
            }
            total += quotient;
        }
    }

    *sum = total;
    return 1;
}

int main(void)
{
    enum { INPUT_SIZE = 128 };
    char input[INPUT_SIZE];
    char *start;
    char *end;
    uintmax_t parsed;
    uint64_t sum;
    int ch;

    if (fgets(input, sizeof input, stdin) == NULL) {
        fputs("Failed to read input.\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; input[i] != '\0'; ++i) {
        if (input[i] == '\n') {
            input[i] = '\0';
            break;
        }
    }

    if (ferror(stdin)) {
        fputs("Failed to read input.\n", stderr);
        return EXIT_FAILURE;
    }

    {
        size_t i = 0;

        while (input[i] != '\0' && input[i] != '\n') {
            ++i;
        }

        if (input[i] == '\0' && i == sizeof input - 1) {
            ch = fgetc(stdin);

            if (ch != '\n' && ch != EOF) {
                while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
                }

                fputs("Input is too long.\n", stderr);
                return EXIT_FAILURE;
            }

            if (ferror(stdin)) {
                fputs("Failed to read input.\n", stderr);
                return EXIT_FAILURE;
            }
        }
    }

    start = input;

    while (is_space_char(*start)) {
        ++start;
    }

    if (*start == '-' || *start == '\0') {
        fputs("Invalid positive integer.\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    parsed = strtoumax(start, &end, 10);

    if (errno == ERANGE || end == start || parsed == 0 ||
        parsed > UINT64_MAX) {
        fputs("Invalid positive integer.\n", stderr);
        return EXIT_FAILURE;
    }

    while (is_space_char(*end)) {
        ++end;
    }

    if (*end != '\0') {
        fputs("Invalid positive integer.\n", stderr);
        return EXIT_FAILURE;
    }

    if (!sum_even_factors((uint64_t)parsed, &sum)) {
        fputs("Unable to calculate the sum.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", sum) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}