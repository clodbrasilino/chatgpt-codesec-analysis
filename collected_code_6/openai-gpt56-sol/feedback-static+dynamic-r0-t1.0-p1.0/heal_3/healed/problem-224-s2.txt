#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static unsigned int count_set_bits(uint64_t value)
{
    unsigned int count = 0;

    while (value != UINT64_C(0)) {
        value &= value - UINT64_C(1);
        ++count;
    }

    return count;
}

int main(void)
{
    uintmax_t parsed_value;
    int ch;

    while ((ch = getchar()) != EOF && isspace((unsigned char)ch)) {
    }

    if (ch == EOF || ch == '-') {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (ungetc(ch, stdin) == EOF) {
        return EXIT_FAILURE;
    }

    errno = 0;

    if (scanf("%" SCNuMAX, &parsed_value) != 1 ||
        errno == ERANGE ||
        parsed_value > UINT64_MAX) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    while ((ch = getchar()) != EOF) {
        if (!isspace((unsigned char)ch)) {
            fputs("Invalid input\n", stderr);
            return EXIT_FAILURE;
        }
    }

    if (ferror(stdin)) {
        return EXIT_FAILURE;
    }

    if (printf("%u\n", count_set_bits((uint64_t)parsed_value)) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}