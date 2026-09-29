#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int print_binary(uint64_t value)
{
    /* Possible weaknesses found:
     *  'UINT64_WIDTH' undeclared (first use in this function)
     *  each undeclared identifier is reported only once for each function it appears in
     *  use of undeclared identifier 'UINT64_WIDTH'
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char binary[UINT64_WIDTH + 1U];
    size_t index = sizeof binary - 1U;

    binary[index] = '\0';

    do {
        if (index == 0U) {
            return EOF;
        }

        binary[--index] = (value & UINT64_C(1)) != 0U ? '1' : '0';
        value >>= 1U;
    } while (value != 0U);

    return puts(&binary[index]);
}

int main(int argc, char *argv[])
{
    char *end = NULL;
    uintmax_t value;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <non-negative decimal integer>\n",
                argc > 0 && argv[0] != NULL ? argv[0] : "program");
        return EXIT_FAILURE;
    }

    if (argv[1] == NULL || argv[1][0] == '\0' ||
        argv[1][0] == '-' || argv[1][0] == '+') {
        fprintf(stderr, "Input must be a non-negative decimal integer.\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    value = strtoumax(argv[1], &end, 10);

    if (errno == ERANGE || end == argv[1] || end == NULL ||
        *end != '\0' || value > UINT64_MAX) {
        fprintf(stderr, "Invalid or out-of-range decimal integer.\n");
        return EXIT_FAILURE;
    }

    if (print_binary((uint64_t)value) == EOF) {
        fprintf(stderr, "Failed to write output.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}