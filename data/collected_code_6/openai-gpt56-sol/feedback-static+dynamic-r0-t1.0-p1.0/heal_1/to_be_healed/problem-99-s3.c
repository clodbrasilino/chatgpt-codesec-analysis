#include <errno.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

static void print_binary(uint64_t value)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char binary[65];
    size_t index = sizeof(binary);

    binary[--index] = '\0';

    do {
        binary[--index] = (char)('0' + (value & UINT64_C(1)));
        value >>= 1;
    } while (value != 0);

    puts(&binary[index]);
}

int main(int argc, char *argv[])
{
    char *end = NULL;
    uintmax_t value;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <non-negative decimal integer>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (argv[1][0] == '-') {
        fprintf(stderr, "Input must be a non-negative decimal integer.\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    value = strtoumax(argv[1], &end, 10);

    if (errno == ERANGE || end == argv[1] || *end != '\0' || value > UINT64_MAX) {
        fprintf(stderr, "Invalid or out-of-range decimal integer.\n");
        return EXIT_FAILURE;
    }

    print_binary((uint64_t)value);

    if (ferror(stdout)) {
        fprintf(stderr, "Failed to write output.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}