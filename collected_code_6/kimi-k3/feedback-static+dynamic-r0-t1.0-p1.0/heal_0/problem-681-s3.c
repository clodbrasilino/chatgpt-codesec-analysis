#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int smallest_prime_divisor(int n) {
    if (n < 2) {
        return -1;
    }
    if (n % 2 == 0) {
        return 2;
    }
    for (int i = 3; i <= n / i; i += 2) {
        if (n % i == 0) {
            return i;
        }
    }
    return n;
}

int main(void) {
    int number;
    printf("Enter a positive integer greater than 1: ");
    if (scanf("%d", &number) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    int result = smallest_prime_divisor(number);
    if (result == -1) {
        fprintf(stderr, "Number must be greater than 1\n");
        return EXIT_FAILURE;
    }
    printf("Smallest prime divisor of %d is %d\n", number, result);
    return EXIT_SUCCESS;
}