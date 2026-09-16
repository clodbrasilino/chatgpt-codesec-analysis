#include <stdio.h>
#include <stdlib.h>

double calculate_harmonic_sum(int n) {
    if (n <= 1) {
        return 0.0;
    }

    double sum = 0.0;
    for (int i = 1; i < n; i++) {
        sum += 1.0 / i;
    }

    return sum;
}

int main(void) {
    int n = 5;
    double result = calculate_harmonic_sum(n);
    printf("%f\n", result);

    n = 0;
    result = calculate_harmonic_sum(n);
    printf("%f\n", result);

    return 0;
}