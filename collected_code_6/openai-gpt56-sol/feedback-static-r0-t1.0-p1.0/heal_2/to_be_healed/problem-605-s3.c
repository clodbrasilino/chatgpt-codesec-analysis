#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

static int is_prime(int value)
{
    int divisor;

    if (value < 2) {
        return 0;
    }

    if (value == 2) {
        return 1;
    }

    if (value % 2 == 0) {
        return 0;
    }

    for (divisor = 3; divisor <= value / divisor; divisor += 2) {
        if (value % divisor == 0) {
            return 0;
        }
    }

    return 1;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[])
{
    char *end;
    long value;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <integer>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    value = strtol(argv[1], &end, 10);

    if (errno == ERANGE || end == argv[1] || *end != '\0' ||
        value < INT_MIN || value > INT_MAX) {
        fprintf(stderr, "Invalid integer\n");
        return EXIT_FAILURE;
    }

    if (printf("%d\n", is_prime((int)value)) < 0) {
        return EXIT_FAILURE;
    }

    if (fflush(stdout) == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}