#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

long long gcd(long long a, long long b) {
    while (b != 0) {
        long long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

long long smallest_multiple(int n) {
    if (n < 1) {
        return 0;
    }
    long long result = 1;
    for (int i = 2; i <= n; i++) {
        long long common_divisor = gcd(result, i);
        if (result > LLONG_MAX / (i / common_divisor)) {
            return -1;
        }
        result = result * (i / common_divisor);
    }
    return result;
}

int main(int argc, char * const argv[const]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <n>\n", argv[0]);
        return EXIT_FAILURE;
    }
    char *endptr;
    long val = strtol(argv[1], &endptr, 10);
    if (*endptr != '\0' || val < 1 || val > 40) {
        fprintf(stderr, "Error: n must be an integer between 1 and 40\n");
        return EXIT_FAILURE;
    }
    long long res = smallest_multiple((int)val);
    if (res == -1) {
        fprintf(stderr, "Error: Integer overflow detected\n");
        return EXIT_FAILURE;
    }
    printf("%lld\n", res);
    return EXIT_SUCCESS;
}