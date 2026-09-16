#include <errno.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

static unsigned int last_digit_of_factorial(uint64_t number)
{
    static const unsigned int digits[] = {1U, 1U, 2U, 6U, 4U};

    return number >= 5U ? 0U : digits[number];
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
        fprintf(stderr, "Invalid non-negative integer: %s\n", argv[1]);
        return EXIT_FAILURE;
    }

    printf("%u\n", last_digit_of_factorial((uint64_t)number));

    return EXIT_SUCCESS;
}