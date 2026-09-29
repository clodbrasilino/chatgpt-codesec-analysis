#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define UINT64_BITS 64U

static int print_binary(uint64_t value)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char binary[UINT64_BITS + 1U];
    size_t index = sizeof(binary) - 1U;

    binary[index] = '\0';

    do {
        if (index == 0U) {
            return -1;
        }

        --index;
        binary[index] = (value & UINT64_C(1)) != UINT64_C(0) ? '1' : '0';
        value >>= 1U;
    } while (value != UINT64_C(0));

    if (fputs(binary + index, stdout) == EOF) {
        return -1;
    }

    return fputc('\n', stdout) == EOF ? -1 : 0;
}

int main(int argc, char *argv[])
{
    char *end;
    uintmax_t value;
    const char *program;

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