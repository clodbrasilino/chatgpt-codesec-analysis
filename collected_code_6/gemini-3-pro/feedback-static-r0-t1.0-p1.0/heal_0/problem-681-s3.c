#include <stdio.h>
#include <stdlib.h>

unsigned long long find_smallest_prime_divisor(unsigned long long n) {
    if (n <= 1) {
        return 0; 
    }
    if (n % 2 == 0) {
        return 2;
    }
    if (n % 3 == 0) {
        return 3;
    }

    for (unsigned long long i = 5; i * i <= n; i += 6) {
        if (n % i == 0) {
            return i;
        }
        if (n % (i + 2) == 0) {
            return (i + 2);
        }
    }

    return n;
}

int main(void) {
    unsigned long long n;
    int result;

    result = scanf("%llu", &n);
    if (result != 1) {
        fprintf(stderr, "Invalid input.\n");
        return EXIT_FAILURE;
    }

    unsigned long long smallest_prime_divisor = find_smallest_prime_divisor(n);

    if (smallest_prime_divisor == 0) {
        printf("No prime divisor exists for the given number.\n");
    } else {
        printf("Smallest prime divisor of %llu is %llu\n", n, smallest_prime_divisor);
    }

    return EXIT_SUCCESS;
}