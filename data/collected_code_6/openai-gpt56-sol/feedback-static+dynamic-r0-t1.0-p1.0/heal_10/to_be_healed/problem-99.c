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
    size_t index = sizeof(binary);

    binary[--index] = '\0';

    do {
        if (index == 0U) {
            return -1;
        }

        binary[--index] = (value & UINT64_C(1)) ? '1' : '0';
        value >>= 1U;
    } while (value != UINT64_C(0));

    if (fwrite(binary + index, 1U, UINT64_BINARY_WIDTH - index, stdout)
            != UINT64_BINARY_WIDTH - index ||
        fputc('\n', stdout) == EOF) {
        return -1;
    }

    return 0;
}

int main(int argc, char *argv[])
{
    const char *program = "program";
    char *end = NULL;
    uintmax_t value;

    if (argc > 0 && argv != NULL && argv[0] != NULL) {
        program = argv[0];
    }

    if (argc != 2 || argv == NULL || argv[1] == NULL) {
        fprintf(stderr, "Usage: %s <nonnegative decimal integer>\n", program);
        return EXIT_FAILURE;
    }

    if (argv[1][0] == '\0' || argv[1][0] == '-' || argv[1][0] == '+') {
        fputs("Invalid decimal integer\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    value = strtoumax(argv[1], &end, 10);

    if (errno == ERANGE ||
        end == argv[1] ||
        end == NULL ||
        *end != '\0' ||
        value > UINT64_MAX) {
        fputs("Invalid decimal integer\n", stderr);
        return EXIT_FAILURE;
    }

    if (print_binary((uint64_t)value) != 0) {
        fputs("Output error\n", stderr);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}