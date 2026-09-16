#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static unsigned int count_digits(intmax_t number)
{
    unsigned int count = 1;
    uintmax_t magnitude;

    if (number < 0) {
        magnitude = (uintmax_t)(-(number + 1)) + UINTMAX_C(1);
    } else {
        magnitude = (uintmax_t)number;
    }

    while (magnitude >= UINTMAX_C(10)) {
        magnitude /= UINTMAX_C(10);
        ++count;
    }

    return count;
}

int main(int argc, char * const argv[])
{
    char *end = NULL;
    intmax_t number;

    if (argc != 2) {
        (void)fprintf(stderr, "Usage: %s <integer>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    number = strtoimax(argv[1], &end, 10);

    if (errno == ERANGE || end == argv[1] || *end != '\0') {
        (void)fprintf(stderr, "Invalid integer: %s\n", argv[1]);
        return EXIT_FAILURE;
    }

    if (printf("%u\n", count_digits(number)) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}