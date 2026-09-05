#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

unsigned int compute_gcd(unsigned int a, unsigned int b) {
    while (b != 0) {
        unsigned int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

unsigned long long compute_lcm(unsigned int a, unsigned int b) {
    if (a == 0 || b == 0) {
        return 0;
    }
    unsigned long long gcd = compute_gcd(a, b);
    return ((unsigned long long)a / gcd) * b;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[const]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <positive_integer> <positive_integer>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *endptr1;
    char *endptr2;
    unsigned long val1 = strtoul(argv[1], &endptr1, 10);
    unsigned long val2 = strtoul(argv[2], &endptr2, 10);

    if (*endptr1 != '\0' || *endptr2 != '\0') {
        fprintf(stderr, "Invalid input: Arguments must be integers.\n");
        return EXIT_FAILURE;
    }

    if (val1 == 0 || val2 == 0) {
        fprintf(stderr, "Invalid input: Arguments must be positive integers.\n");
        return EXIT_FAILURE;
    }

    if (val1 > UINT_MAX || val2 > UINT_MAX) {
        fprintf(stderr, "Invalid input: Arguments out of range.\n");
        return EXIT_FAILURE;
    }

    unsigned int a = (unsigned int)val1;
    unsigned int b = (unsigned int)val2;

    unsigned long long result = compute_lcm(a, b);

    printf("%llu\n", result);

    return EXIT_SUCCESS;
}