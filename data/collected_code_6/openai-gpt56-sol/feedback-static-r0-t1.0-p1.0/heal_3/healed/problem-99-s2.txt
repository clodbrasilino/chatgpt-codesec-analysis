#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

static int print_binary(unsigned long long value)
{
    char binary[sizeof(value) * CHAR_BIT + 1];
    size_t index = sizeof(binary) - 1;

    binary[index] = '\0';

    do {
        if (index == 0) {
            return -1;
        }

        binary[--index] = (char)('0' + (value & 1ULL));
        value >>= 1;
    } while (value != 0);

    if (fputs(&binary[index], stdout) == EOF) {
        return -1;
    }

    return fputc('\n', stdout) == EOF ? -1 : 0;
}

int main(int argc, char *argv[])
{
    char *end;
    unsigned long long value;

    if (argc != 2) {
        const char *program =
            argc > 0 && argv != NULL && argv[0] != NULL ? argv[0] : "program";

        fprintf(stderr, "Usage: %s <nonnegative decimal number>\n", program);
        return EXIT_FAILURE;
    }

    if (argv == NULL || argv[1] == NULL || argv[1][0] == '\0' ||
        argv[1][0] == '-') {
        fputs("Error: the number must be a nonnegative decimal integer.\n",
              stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    end = NULL;
    value = strtoull(argv[1], &end, 10);

    if (errno == ERANGE || end == NULL || end == argv[1] || *end != '\0') {
        fputs("Error: invalid or out-of-range decimal number.\n", stderr);
        return EXIT_FAILURE;
    }

    if (print_binary(value) != 0) {
        fputs("Error: failed to write output.\n", stderr);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}