#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool is_non_prime(long long n);

bool is_non_prime(long long n) {
    if (n <= 1) {
        return true;
    }
    if (n == 2) {
        return false;
    }
    if (n % 2 == 0) {
        return true;
    }
    for (long long i = 3; i <= n / i; i += 2) {
        if (n % i == 0) {
            return true;
        }
    }
    return false;
}

int main(void) {
    long long number;

    if (scanf("%lld", &number) != 1) {
        return 1;
    }

    if (is_non_prime(number)) {
        printf("Non-Prime\n");
    } else {
        printf("Prime\n");
    }

    return 0;
}