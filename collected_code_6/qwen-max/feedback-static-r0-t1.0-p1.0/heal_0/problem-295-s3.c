#include <stdio.h>
#include <stdlib.h>

int sum_of_divisors(int n) {
    int sum = 0;
    for (int i = 1; i <= n; i++) {
        if (n % i == 0) {
            sum += i;
        }
    }
    return sum;
}

int main() {
    int number;
    printf("Enter a number: ");
    if (scanf("%d", &number) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    int result = sum_of_divisors(number);
    printf("Sum of divisors: %d\n", result);
    return EXIT_SUCCESS;
}