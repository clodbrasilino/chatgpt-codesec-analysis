#include <stdio.h>
#include <stdlib.h>

unsigned long long find_nsw_prime(int n) {
    if (n == 1) {
        return 1;
    }
    unsigned long long a = 1;
    unsigned long long b = 1;
    for (int i = 2; i <= n; i++) {
        unsigned long long c = 2 * b + a;
        a = b;
        b = c;
    }
    return b;
}

int main(int argc, char * const argv[const]) {
    if (argc != 2) {
        return EXIT_FAILURE;
    }
    char *endptr;
    long val = strtol(argv[1], &endptr, 10);
    if (*endptr != '\0' || val <= 0) {
        return EXIT_FAILURE;
    }
    int n = (int)val;
    unsigned long long result = find_nsw_prime(n);
    printf("%llu\n", result);
    return EXIT_SUCCESS;
}