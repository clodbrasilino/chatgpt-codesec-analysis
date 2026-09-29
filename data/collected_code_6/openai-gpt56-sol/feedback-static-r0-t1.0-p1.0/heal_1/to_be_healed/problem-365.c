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
        magnitude = (uintmax_t)(-(number + 1)) + 1U;
    } else {
        magnitude = (uintmax_t)number;
    }

    while (magnitude >= 10U) {
        magnitude /= 10U;
        ++count;
    }

    return count;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[])
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