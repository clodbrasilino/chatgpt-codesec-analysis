#include <stdio.h>
#include <stdlib.h>

double calculate_harmonic_sum(int n);

double calculate_harmonic_sum(int n) {
    if (n <= 1) {
        return 0.0;
    }

    double sum = 0.0;
    for (int i = 1; i <= n - 1; ++i) {
        sum += 1.0 / i;
    }

    return sum;
}

int main(void) {
    int n = 0;
    double result = 0.0;
    int input_status = 0;

    input_status = scanf("%d", &n);
    if (input_status != 1) {
        return EXIT_FAILURE;
    }

    if (n <= 1) {
        return EXIT_FAILURE;
    }

    result = calculate_harmonic_sum(n);
    printf("%f\n", result);

    return EXIT_SUCCESS;
}