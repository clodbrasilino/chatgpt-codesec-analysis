#include <stdio.h>
#include <stdlib.h>

long long binomial_coefficient(int n, int k) {
    if (k < 0 || k > n || n < 0) {
        return 0;
    }
    if (k == 0 || k == n) {
        return 1;
    }
    if (k > n - k) {
        k = n - k;
    }
    long long result = 1;
    for (int i = 0; i < k; i++) {
        result = result * (n - i) / (i + 1);
    }
    return result;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s n k\n", argv[0]);
        return EXIT_FAILURE;
    }
    char *endptr;
    long n = strtol(argv[1], &endptr, 10);
    if (*endptr != '\0' || n < 0) {
        fprintf(stderr, "Invalid n\n");
        return EXIT_FAILURE;
    }
    long k = strtol(argv[2], &endptr, 10);
    if (*endptr != '\0' || k < 0) {
        fprintf(stderr, "Invalid k\n");
        return EXIT_FAILURE;
    }
    if (n > 67) {
        fprintf(stderr, "n too large\n");
        return EXIT_FAILURE;
    }
    printf("%lld\n", binomial_coefficient((int)n, (int)k));
    return EXIT_SUCCESS;
}