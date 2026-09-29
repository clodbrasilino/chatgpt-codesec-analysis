#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int print_binary(uint64_t value)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     *  use of undeclared identifier 'UINT64_WIDTH'
     *  'UINT64_WIDTH' undeclared (first use in this function)
     *  each undeclared identifier is reported only once for each function it appears in
     */
    char binary[UINT64_WIDTH + 1U];
    size_t index = sizeof(binary) - 1U;

    binary[index] = '\0';

    do {
        binary[--index] = (char)('0' + (value & UINT64_C(1)));
        value >>= 1U;
    } while (value != UINT64_C(0));

    return printf("%s\n", &binary[index]) < 0 ? -1 : 0;
}

int main(int argc, char *argv[])
{
    char *end = NULL;
    uintmax_t value;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <non-negative decimal integer>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (argv[1][0] == '\0' || argv[1][0] == '-') {
        fputs("Input must be a non-negative decimal integer.\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    value = strtoumax(argv[1], &end, 10);

    if (errno == ERANGE ||
        end == argv[1] ||
        *end != '\0' ||
        value > UINT64_MAX) {
        fputs("Invalid or out-of-range decimal integer.\n", stderr);
        return EXIT_FAILURE;
    }

    if (print_binary((uint64_t)value) != 0) {
        fputs("Failed to write output.\n", stderr);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}