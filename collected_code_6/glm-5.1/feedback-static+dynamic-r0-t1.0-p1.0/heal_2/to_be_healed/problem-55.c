#include <stdio.h>
#include <stdlib.h>

long long geometric_term(int a, int r, int n) {
    if (n < 0) {
        return 0;
    }
    if (n == 0) {
        return 1;
    }
    long long result = 1;
    long long base = r;
    int exp = n;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result *= base;
        }
        base *= base;
        exp /= 2;
    }
    return result * a;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[]) {
    if (argc != 4) {
        return EXIT_FAILURE;
    }
    char *endptr_a, *endptr_r, *endptr_n;
    long a = strtol(argv[1], &endptr_a, 10);
    long r = strtol(argv[2], &endptr_r, 10);
    long n = strtol(argv[3], &endptr_n, 10);
    if (*endptr_a != '\0' || *endptr_r != '\0' || *endptr_n != '\0') {
        return EXIT_FAILURE;
    }
    if (n < 0) {
        return EXIT_FAILURE;
    }
    long long term = geometric_term((int)a, (int)r, (int)n);
    printf("%lld\n", term);
    return EXIT_SUCCESS;
}