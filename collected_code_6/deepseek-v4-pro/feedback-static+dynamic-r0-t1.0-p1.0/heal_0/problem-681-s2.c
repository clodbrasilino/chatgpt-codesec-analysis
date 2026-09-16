#include <stdio.h>
#include <stdlib.h>

int smallest_prime_divisor(int n) {
    if (n <= 1) {
        return -1;
    }
    if (n % 2 == 0) {
        return 2;
    }
    for (int i = 3; i * i <= n; i += 2) {
        if (n % i == 0) {
            return i;
        }
    }
    return n;
}

int main(void) {
    int number;
    
    printf("Enter a number: ");
    if (scanf("%d", &number) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    int result = smallest_prime_divisor(number);
    
    if (result == -1) {
        printf("Number must be greater than 1\n");
    } else {
        printf("Smallest prime divisor: %d\n", result);
    }
    
    return EXIT_SUCCESS;
}