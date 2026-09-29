#include <stdio.h>
#include <stdlib.h>

double sum_of_inverse_divisors(int n) {
    if (n <= 0) {
        return 0.0;
    }

    double sum = 0.0;
    for (int i = 1; i <= n; i++) {
        if (n % i == 0) {
            sum += 1.0 / (double)i;
        }
    }
    return sum;
}

int main(void) {
    int number;
    
    if (scanf("%d", &number) != 1) {
        return EXIT_FAILURE;
    }

    if (number <= 0) {
        return EXIT_FAILURE;
    }

    double result = sum_of_inverse_divisors(number);
    printf("%f\n", result);

    return EXIT_SUCCESS;
}