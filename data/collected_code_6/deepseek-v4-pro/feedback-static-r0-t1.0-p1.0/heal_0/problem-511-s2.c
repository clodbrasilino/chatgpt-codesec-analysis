#include <stdio.h>
#include <stdlib.h>

int min_sum_of_factors(int n) {
    int sum = n + 1;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            int factor1 = i;
            int factor2 = n / i;
            int current_sum = factor1 + factor2;
            if (current_sum < sum) {
                sum = current_sum;
            }
        }
    }
    return sum;
}

int main(void) {
    int number;
    printf("Enter a number: ");
    if (scanf("%d", &number) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    if (number < 1) {
        fprintf(stderr, "Number must be positive\n");
        return EXIT_FAILURE;
    }
    int result = min_sum_of_factors(number);
    printf("Minimum sum of factors: %d\n", result);
    return 0;
}