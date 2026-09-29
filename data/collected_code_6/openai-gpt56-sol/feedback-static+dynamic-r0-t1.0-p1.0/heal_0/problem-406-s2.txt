#include <errno.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

static unsigned int parity(uintmax_t number)
{
    unsigned int result = 0U;

    while (number != 0U) {
        result ^= 1U;
        number &= number - 1U;
    }

    return result;
}

int main(int argc, char *argv[])
{
    char *end = NULL;
    uintmax_t number;

    if (argc != 2) {
        (void)fprintf(stderr, "Usage: %s <nonnegative integer>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    number = strtoumax(argv[1], &end, 0);

    if (errno == ERANGE || end == argv[1] || *end != '\0' || argv[1][0] == '-') {
        (void)fprintf(stderr, "Invalid nonnegative integer: %s\n", argv[1]);
        return EXIT_FAILURE;
    }

    (void)printf("%u\n", parity(number));
    return EXIT_SUCCESS;
}