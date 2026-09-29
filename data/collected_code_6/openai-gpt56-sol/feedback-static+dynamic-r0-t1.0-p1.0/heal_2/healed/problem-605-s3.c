#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

static int is_prime(int value)
{
    if (value < 2) {
        return 0;
    }

    if (value == 2) {
        return 1;
    }

    if (value % 2 == 0) {
        return 0;
    }

    for (int divisor = 3; divisor <= value / divisor; divisor += 2) {
        if (value % divisor == 0) {
            return 0;
        }
    }

    return 1;
}

int main(int argc, const char *const argv[])
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

    printf("%d\n", is_prime((int)value));

    if (fflush(stdout) == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}