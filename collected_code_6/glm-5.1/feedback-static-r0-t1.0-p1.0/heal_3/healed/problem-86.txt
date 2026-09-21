#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

unsigned long long centered_hexical(int n) {
    if (n < 1) {
        return 0;
    }
    return (unsigned long long)(3 * n - 2) * n;
}

int main(int argc, char * const argv[const]) {
    if (argc != 2) {
        return EXIT_FAILURE;
    }

    char *endptr;
    errno = 0;
    long val = strtol(argv[1], &endptr, 10);

    if (errno != 0 || *endptr != '\0' || val < 1 || val > INT_MAX) {
        return EXIT_FAILURE;
    }

    unsigned long long result = centered_hexical((int)val);
    printf("%llu\n", result);

    return EXIT_SUCCESS;
}