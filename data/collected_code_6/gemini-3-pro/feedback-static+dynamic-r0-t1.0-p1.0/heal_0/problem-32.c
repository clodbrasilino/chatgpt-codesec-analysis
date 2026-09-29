#include <stdio.h>
#include <stdlib.h>

long long int largestPrimeFactor(long long int n) {
    if (n <= 1) {
        return 0;
    }

    long long int maxPrime = -1;

    while (n % 2 == 0) {
        maxPrime = 2;
        n >>= 1;
    }

    for (long long int i = 3; i * i <= n; i += 2) {
        while (n % i == 0) {
            maxPrime = i;
            n /= i;
        }
    }

    if (n > 2) {
        maxPrime = n;
    }

    return maxPrime;
}

int main(void) {
    long long int num = 0;
    long long int result = 0;

    if (scanf("%lld", &num) != 1) {
        return EXIT_FAILURE;
    }

    result = largestPrimeFactor(num);

    if (result == 0) {
        printf("No prime factors.\n");
    } else {
        printf("%lld\n", result);
    }

    return EXIT_SUCCESS;
}