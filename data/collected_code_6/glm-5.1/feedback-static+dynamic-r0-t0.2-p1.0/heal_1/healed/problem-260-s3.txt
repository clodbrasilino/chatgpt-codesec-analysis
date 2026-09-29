#include <stdio.h>
#include <stdlib.h>

unsigned long long nsw_prime(int n) {
    if (n <= 0) {
        return 0;
    }
    if (n == 1) {
        return 1;
    }
    unsigned long long prev2 = 1;
    unsigned long long prev1 = 1;
    unsigned long long current = 0;
    for (int i = 2; i <= n; i++) {
        current = 2 * prev1 + prev2;
        prev2 = prev1;
        prev1 = current;
    }
    return current;
}

int main(int argc, char * const argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <n>\n", argv[0]);
        return EXIT_FAILURE;
    }
    char *endptr;
    long val = strtol(argv[1], &endptr, 10);
    if (*endptr != '\0' || val <= 0) {
        fprintf(stderr, "Error: n must be a positive integer.\n");
        return EXIT_FAILURE;
    }
    unsigned long long result = nsw_prime((int)val);
    printf("%llu\n", result);
    return EXIT_SUCCESS;
}