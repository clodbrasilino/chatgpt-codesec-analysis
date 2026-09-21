#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int print_binary(uint64_t value)
{
    unsigned int bit = 64U;

    while (bit > 1U && ((value >> (bit - 1U)) & UINT64_C(1)) == 0U) {
        --bit;
    }

    do {
        --bit;
        if (fputc(((value >> bit) & UINT64_C(1)) != 0U ? '1' : '0',
                  stdout) == EOF) {
            return -1;
        }
    } while (bit != 0U);

    return fputc('\n', stdout) == EOF ? -1 : 0;
}

int main(int argc, char *argv[])
{
    const char *program;
    char *end;
    uintmax_t value;

    program = argc > 0 && argv != NULL && argv[0] != NULL
                  ? argv[0]
                  : "program";

    if (argc != 2 || argv == NULL || argv[1] == NULL) {
        fprintf(stderr, "Usage: %s <non-negative decimal integer>\n", program);
        return EXIT_FAILURE;
    }

    if (argv[1][0] == '\0' || argv[1][0] == '-') {
        fputs("Input must be a non-negative decimal integer.\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    end = NULL;
    value = strtoumax(argv[1], &end, 10);

    if (errno == ERANGE || end == NULL || end == argv[1] ||
        *end != '\0' || value > UINT64_MAX) {
        fputs("Invalid or out-of-range decimal integer.\n", stderr);
        return EXIT_FAILURE;
    }

    if (print_binary((uint64_t)value) != 0) {
        fputs("Failed to write output.\n", stderr);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}