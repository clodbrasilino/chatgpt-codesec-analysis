#include <stdio.h>
#include <stdlib.h>

unsigned long long calculate_pell(int n) {
    if (n < 0) {
        return 0;
    }
    if (n == 0) {
        return 0;
    }
    if (n == 1) {
        return 1;
    }
    unsigned long long a = 0;
    unsigned long long b = 1;
    for (int i = 2; i <= n; i++) {
        unsigned long long c = 2 * b + a;
        a = b;
        b = c;
    }
    return b;
}

int main(int argc, char * const * const argv) {
    if (argc != 2) {
        return EXIT_FAILURE;
    }
    int n = atoi(argv[1]);
    if (n < 0) {
        return EXIT_FAILURE;
    }
    unsigned long long result = calculate_pell(n);
    printf("%llu\n", result);
    return EXIT_SUCCESS;
}