#include <stdio.h>
#include <stdlib.h>

unsigned long long centered_hexagonal(int n) {
    if (n < 1) {
        return 0;
    }
    return (unsigned long long)(3 * n - 1) * n - (unsigned long long)n + (unsigned long long)(n * n);
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    if (argc != 2) {
        return EXIT_FAILURE;
    }

    char *endptr;
    long val = strtol(argv[1], &endptr, 10);

    if (*endptr != '\0' || val < 1) {
        return EXIT_FAILURE;
    }

    unsigned long long result = centered_hexagonal((int)val);
    printf("%llu\n", result);

    return EXIT_SUCCESS;
}