#include <stdio.h>
#include <stdlib.h>

long long tetrahedral(int n) {
    if (n < 0) {
        return -1;
    }
    if (n == 0) {
        return 0;
    }
    return (long long)n * (n + 1) * (n + 2) / 6;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <n>\n", argv[0]);
        return EXIT_FAILURE;
    }
    
    char *endptr;
    long val = strtol(argv[1], &endptr, 10);
    if (*endptr != '\0' || endptr == argv[1]) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    if (val < 0 || val > 1000000) {
        fprintf(stderr, "Input out of range\n");
        return EXIT_FAILURE;
    }
    
    long long result = tetrahedral((int)val);
    printf("%lld\n", result);
    return EXIT_SUCCESS;
}