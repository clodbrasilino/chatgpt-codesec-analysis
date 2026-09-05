#include <stdio.h>
#include <stdlib.h>

long long gcd(long long a, long long b) {
    long long temp;
    while (b != 0) {
        temp = b;
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
    long long current_gcd;
    for (int i = 2; i <= n; i++) {
        current_gcd = gcd(result, i);
        if (current_gcd == 0) {
            return 0;
        }
        if (result > 0 && i / current_gcd > LLONG_MAX / result) {
            return 0;
        }
        result = result / current_gcd * i;
    }
    return result;
}

int main(int argc, char *argv[]) {
    int n;
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <n>\n", argv[0]);
        return EXIT_FAILURE;
    }
    n = atoi(argv[1]);
    if (n < 1) {
        fprintf(stderr, "Error: n must be a positive integer.\n");
        return EXIT_FAILURE;
    }
    long long result = smallest_multiple(n);
    if (result == 0) {
        fprintf(stderr, "Error: Overflow detected or invalid input.\n");
        return EXIT_FAILURE;
    }
    printf("%lld\n", result);
    return EXIT_SUCCESS;
}