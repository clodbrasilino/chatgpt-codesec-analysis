#include <stdio.h>

long long largest_prime_factor(long long n) {
    if (n <= 1) {
        return -1;
    }

    long long largest = -1;

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
    long long number = 600851475143; 
    long long result = largest_prime_factor(number);

    if (result != -1) {
        printf("%lld\n", result);
    } else {
        printf("No prime factor found.\n");
    }

    return 0;
}