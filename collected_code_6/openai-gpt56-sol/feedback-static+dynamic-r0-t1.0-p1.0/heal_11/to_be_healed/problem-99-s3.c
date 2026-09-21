#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define UINT64_BINARY_WIDTH 64U

static int print_binary(uint64_t value)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char binary[UINT64_BINARY_WIDTH + 1U];
    size_t index = UINT64_BINARY_WIDTH;

    binary[index] = '\0';

    do {
        if (index == 0U) {
            return EOF;
        }

        --index;
        binary[index] = (value & UINT64_C(1)) != 0U ? '1' : '0';
        value >>= 1U;
    } while (value != 0U);

    if (fputs(binary + index, stdout) == EOF) {
        return EOF;
    }

    return fputc('\n', stdout) == EOF ? EOF : 0;
}

int main(int argc, char *argv[])
{
    char *end;
    uintmax_t value;

    if (argc != 2 || argv == NULL || argv[1] == NULL) {
        const char *program_name =
            argc > 0 && argv != NULL && argv[0] != NULL
                ? argv[0]
                : "program";

        fprintf(stderr, "Usage: %s <non-negative decimal integer>\n",
                program_name);
        return EXIT_FAILURE;
    }

    if (argv[1][0] == '\0' || argv[1][0] == '-' || argv[1][0] == '+') {
        fputs("Input must be a non-negative decimal integer.\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    end = NULL;
    value = strtoumax(argv[1], &end, 10);

    if (errno == ERANGE || end == argv[1] || end == NULL ||
        *end != '\0' || value > UINT64_MAX) {
        fputs("Invalid or out-of-range decimal integer.\n", stderr);
        return EXIT_FAILURE;
    }

    if (print_binary((uint64_t)value) == EOF) {
        fputs("Failed to write output.\n", stderr);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}