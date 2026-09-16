#include <stdio.h>
#include <stdlib.h>

static int is_prime(long long n) {
    if (n < 2) return 0;
    if (n % 2 == 0) return n == 2;
    if (n % 3 == 0) return n == 3;
    for (long long i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return 0;
    }
    return 1;
}

long long largest_prime_factor(long long n) {
    long long largest = -1;
    if (n <= 1) return largest;
    if (n < 0) n = -n;

    while (n % 2 == 0) {
        largest = 2;
        n /= 2;
    }

    for (long long i = 3; i * i <= n; i += 2) {
        while (n % i == 0) {
            largest = i;
            n /= i;
        }
    }

    if (n > 2) {
        largest = n;
    }

    return largest;
}

int main(void) {
    printf("%lld\n", largest_prime_factor(13195));
    printf("%lld\n", largest_prime_factor(600851475143LL));
    return 0;
}