#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

static void print_binary(unsigned long long value)
{
    char binary[sizeof(value) * CHAR_BIT + 1U];
    size_t index = sizeof(binary);

    binary[--index] = '\0';

    do {
        binary[--index] = (char)('0' + (value & 1ULL));
        value >>= 1U;
    } while (value != 0ULL);

    puts(&binary[index]);
}

int main(int argc, char *argv[])
{
    char *end = NULL;
    unsigned long long value;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <nonnegative decimal number>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (argv[1][0] == '-') {
        fputs("Error: the number must be nonnegative.\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    value = strtoull(argv[1], &end, 10);

    if (errno == ERANGE || end == argv[1] || *end != '\0') {
        fputs("Error: invalid or out-of-range decimal number.\n", stderr);
        return EXIT_FAILURE;
    }

    print_binary(value);

    if (ferror(stdout)) {
        fputs("Error: failed to write output.\n", stderr);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}