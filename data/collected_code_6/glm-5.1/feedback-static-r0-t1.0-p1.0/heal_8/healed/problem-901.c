#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

unsigned long long gcd(unsigned long long a, unsigned long long b) {
    while (b != 0) {
        unsigned long long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

unsigned long long smallest_multiple(int n) {
    if (n < 1) {
        return 0;
    }
    unsigned long long result = 1;
    for (int i = 2; i <= n; ++i) {
        unsigned long long current_gcd = gcd(result, (unsigned long long)i);
        if (result > ULLONG_MAX / ((unsigned long long)i / current_gcd)) {
            return 0;
        }
        result *= (unsigned long long)i / current_gcd;
    }
    return result;
}

int main(int argc, char const * const argv[]) {
    if (argc != 2) {
        return EXIT_FAILURE;
    }
    char *endptr;
    long val = strtol(argv[1], &endptr, 10);
    if (*endptr != '\0' || val < 1 || val > 40) {
        return EXIT_FAILURE;
    }
    unsigned long long res = smallest_multiple((int)val);
    if (res == 0) {
        return EXIT_FAILURE;
    }
    printf("%llu\n", res);
    return EXIT_SUCCESS;
}