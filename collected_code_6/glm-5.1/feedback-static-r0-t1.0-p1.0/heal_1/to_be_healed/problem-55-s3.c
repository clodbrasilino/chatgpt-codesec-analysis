#include <stdio.h>
#include <stdlib.h>
#include <math.h>

long long find_geometric_term(int a, int r, int n) {
    if (n < 1) {
        return 0;
    }
    if (r == 1) {
        return (long long)a;
    }
    if (n == 1) {
        return (long long)a;
    }
    long long term = (long long)a * (long long)pow(r, n - 1);
    return term;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    if (argc != 4) {
        return EXIT_FAILURE;
    }
    char *endptr_a = NULL;
    char *endptr_r = NULL;
    char *endptr_n = NULL;
    long val_a = strtol(argv[1], &endptr_a, 10);
    long val_r = strtol(argv[2], &endptr_r, 10);
    long val_n = strtol(argv[3], &endptr_n, 10);
    if (*endptr_a != '\0' || *endptr_r != '\0' || *endptr_n != '\0') {
        return EXIT_FAILURE;
    }
    if (val_n < 1 || val_n > 50 || val_a < -1000000 || val_a > 1000000 || val_r < -1000000 || val_r > 1000000) {
        return EXIT_FAILURE;
    }
    long long result = find_geometric_term((int)val_a, (int)val_r, (int)val_n);
    printf("%lld\n", result);
    return EXIT_SUCCESS;
}