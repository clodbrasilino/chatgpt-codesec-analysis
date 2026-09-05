#include <stdio.h>
#include <stdlib.h>

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
    int num;
    printf("Enter a number: ");
    if (scanf("%d", &num) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    int result = smallest_prime_divisor(num);
    if (result == -1) {
        printf("No prime divisor exists for numbers less than 2\n");
    } else {
        printf("Smallest prime divisor: %d\n", result);
    }
    return EXIT_SUCCESS;
}