#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

static long long perrin(int n);

static long long perrin(int n)
{
    if (n == 0) {
        return 3LL;
    }
    if (n == 1) {
        return 0LL;
    }
    if (n == 2) {
        return 2LL;
    }
    return perrin(n - 2) + perrin(n - 3);
}

int main(int argc, char *argv[])
{
    char *endptr = NULL;
    long value = 0L;
    long long result = 0LL;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <n>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    value = strtol(argv[1], &endptr, 10);

    if (errno != 0 || endptr == argv[1] || *endptr != '\0') {
        fprintf(stderr, "Error: invalid number '%s'\n", argv[1]);
        return EXIT_FAILURE;
    }

    if (value < 0L || value > 90L) {
        fprintf(stderr, "Error: n must be between 0 and 90\n");
        return EXIT_FAILURE;
    }

    result = perrin((int)value);

    if (printf("Perrin(%ld) = %lld\n", value, result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}