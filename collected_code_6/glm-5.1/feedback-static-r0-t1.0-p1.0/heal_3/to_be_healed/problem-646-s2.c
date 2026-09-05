#include <stdio.h>
#include <stdlib.h>

long long count_cubes(int n, int k) {
    if (n <= 0 || k <= 0) {
        return 0;
    }
    if (k > n) {
        return 0;
    }
    long long diff = n - k;
    long long side = diff + 1;
    return side * side * side;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[const]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <n> <k>\n", argv[0]);
        return EXIT_FAILURE;
    }
    char *endptr_n, *endptr_k;
    long val_n = strtol(argv[1], &endptr_n, 10);
    long val_k = strtol(argv[2], &endptr_k, 10);
    if (*endptr_n != '\0' || *endptr_k != '\0' || val_n <= 0 || val_k <= 0) {
        fprintf(stderr, "Error: n and k must be positive integers.\n");
        return EXIT_FAILURE;
    }
    long long result = count_cubes((int)val_n, (int)val_k);
    printf("%lld\n", result);
    return EXIT_SUCCESS;
}