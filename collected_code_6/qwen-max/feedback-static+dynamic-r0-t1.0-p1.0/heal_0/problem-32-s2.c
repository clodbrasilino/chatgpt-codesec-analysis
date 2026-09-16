#include <stdio.h>
#include <stdbool.h>

bool is_prime(long n) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    for (long i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return false;
    }
    return true;
}

long largest_prime_factor(long n) {
    long max_prime = -1;
    while (n % 2 == 0) {
        max_prime = 2;
        n /= 2;
    }
    for (long i = 3; i <= n; i += 2) {
        while (n % i == 0) {
            max_prime = i;
            n /= i;
        }
    }
    if (n > 2)
        max_prime = n;

    return max_prime;
}

int main() {
    long number;
    printf("Enter a number: ");
    if (scanf("%ld", &number) != 1) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    if (number <= 0) {
        fprintf(stderr, "Number must be positive\n");
        return 1;
    }

    long result = largest_prime_factor(number);
    printf("The largest prime factor of %ld is %ld\n", number, result);

    return 0;
}