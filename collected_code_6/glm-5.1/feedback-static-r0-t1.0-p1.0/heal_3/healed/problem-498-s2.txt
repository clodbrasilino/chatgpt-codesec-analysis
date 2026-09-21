#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>

unsigned int gcd(unsigned int a, unsigned int b) {
    while (b != 0) {
        unsigned int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int main(int argc, char * const argv[const]) {
    unsigned int a;
    unsigned int b;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <positive_integer_a> <positive_integer_b>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *endptr_a;
    char *endptr_b;
    errno = 0;
    unsigned long val_a = strtoul(argv[1], &endptr_a, 10);
    int err_a = errno;
    unsigned long val_b = strtoul(argv[2], &endptr_b, 10);
    int err_b = errno;

    if (err_a != 0 || err_b != 0 || *endptr_a != '\0' || *endptr_b != '\0' || val_a == 0 || val_b == 0 || val_a > UINT_MAX || val_b > UINT_MAX) {
        fprintf(stderr, "Error: Both arguments must be positive integers within valid range.\n");
        return EXIT_FAILURE;
    }

    a = (unsigned int)val_a;
    b = (unsigned int)val_b;

    unsigned int result = gcd(a, b);
    printf("%u\n", result);

    return EXIT_SUCCESS;
}