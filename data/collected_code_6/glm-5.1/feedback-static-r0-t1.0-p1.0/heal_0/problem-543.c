#include <stdio.h>
#include <stdlib.h>

int count_digits(long long n) {
    if (n == 0) return 1;
    if (n < 0) n = -n;
    int count = 0;
    while (n != 0) {
        n /= 10;
        count++;
    }
    return count;
}

long long add_numbers(long long a, long long b, int *overflow) {
    if ((b > 0 && a > LLONG_MAX - b) || (b < 0 && a < LLONG_MIN - b)) {
        *overflow = 1;
        return 0;
    }
    *overflow = 0;
    return a + b;
}

int main() {
    long long a, b;
    int overflow;

    if (scanf("%lld %lld", &a, &b) != 2) {
        return EXIT_FAILURE;
    }

    long long sum = add_numbers(a, b, &overflow);
    
    if (overflow) {
        return EXIT_FAILURE;
    }

    int digits = count_digits(sum);
    printf("%d\n", digits);

    return EXIT_SUCCESS;
}