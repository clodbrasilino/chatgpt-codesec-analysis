#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

static int print_binary(unsigned long long value)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char binary[sizeof(value) * CHAR_BIT];
    size_t index = sizeof(binary);

    do {
        binary[--index] = (char)('0' + (value & 1ULL));
        value >>= 1;
    } while (value != 0);

    if (fwrite(binary + index, 1, sizeof(binary) - index, stdout) !=
        sizeof(binary) - index) {
        return -1;
    }

    return fputc('\n', stdout) == EOF ? -1 : 0;
}

int main(int argc, char *argv[])
{
    const char *program;
    char *end;
    unsigned long long value;

    program = (argc > 0 && argv != NULL && argv[0] != NULL)
                  ? argv[0]
                  : "program";

    if (argc != 2 || argv == NULL || argv[1] == NULL) {
        fprintf(stderr, "Usage: %s <nonnegative decimal number>\n", program);
        return EXIT_FAILURE;
    }

    if (argv[1][0] == '\0' || argv[1][0] == '-') {
        fputs("Error: the number must be a nonnegative decimal integer.\n",
              stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    end = NULL;
    value = strtoull(argv[1], &end, 10);

    if (errno == ERANGE || end == argv[1] || end == NULL || *end != '\0') {
        fputs("Error: invalid or out-of-range decimal number.\n", stderr);
        return EXIT_FAILURE;
    }

    if (print_binary(value) != 0) {
        fputs("Error: failed to write output.\n", stderr);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}