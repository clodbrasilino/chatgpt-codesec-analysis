#include <errno.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

static unsigned int last_two_digits_of_factorial(uint64_t number)
{
    unsigned int result = 1U;

    if (number >= 10U) {
        return 0U;
    }

    for (uint64_t i = 2U; i <= number; ++i) {
        result = (result * (unsigned int)i) % 100U;
    }

    return result;
}

int main(int argc, char *argv[])
{
    char *end = NULL;
    uintmax_t number;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <non-negative integer>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    number = strtoumax(argv[1], &end, 10);

    if (errno == ERANGE || end == argv[1] || *end != '\0' || argv[1][0] == '-') {
        fputs("Invalid non-negative integer.\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%02u\n", last_two_digits_of_factorial((uint64_t)number));
    return EXIT_SUCCESS;
}