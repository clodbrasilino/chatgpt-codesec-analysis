#include <stdio.h>
#include <math.h>

long largestPrimeFactor(long n) {
    long largestPrime = -1;

    while (n % 2 == 0) {
        largestPrime = 2;
        n /= 2;
    }

    for (long i = 3; i <= sqrt(n); i += 2) {
        while (n % i == 0) {
            largestPrime = i;
            n = n / i;
        }
    }

    if (n > 2)
        largestPrime = n;

    return largestPrime;
}

int main() {
    long n;
    printf("Enter a number: ");
    if (scanf("%ld", &n) != 1) {
        printf("Invalid input!\n");
        return 1;
    }
    if (n <= 1) {
        printf("Number must be grater than 1!\n");
        return 1;
    }

    printf("Largest Prime Factor: %ld\n", largestPrimeFactor(n));
    return 0;
}