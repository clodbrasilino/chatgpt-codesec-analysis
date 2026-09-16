#include <errno.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

static int has_even_parity(uintmax_t value)
{
    int parity = 0;

    while (value != 0U) {
        parity ^= 1;
        value &= value - 1U;
    }

    return parity == 0;
}

int main(int argc, char *argv[])
{
    char *end = NULL;
    uintmax_t value;

    if (argc != 2) {
        (void)fprintf(stderr, "Usage: %s <nonnegative-integer>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    value = strtoumax(argv[1], &end, 0);

    if (errno == ERANGE || end == argv[1] || *end != '\0' || argv[1][0] == '-') {
        (void)fprintf(stderr, "Invalid integer: %s\n", argv[1]);
        return EXIT_FAILURE;
    }

    if (printf("%s\n", has_even_parity(value) ? "Even parity" : "Odd parity") < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}