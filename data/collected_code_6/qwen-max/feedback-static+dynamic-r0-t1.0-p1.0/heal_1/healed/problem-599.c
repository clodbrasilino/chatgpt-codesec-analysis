#include <stdio.h>
#include <stdint.h>

void calculateSumAndAverage(int n, int64_t *sum, double *average) {
    *sum = 0;
    for (int i = 1; i <= n; i++) {
        *sum += i;
    }
    if (n > 0) {
        *average = (double)*sum / n;
    } else {
        *average = 0.0;
    }
}

int main() {
    int n;
    printf("Enter the value of n: ");
    if (scanf("%d", &n) != 1) {
        printf("Invalid input.\n");
        return 1;
    }

    int64_t sum;
    double average;

    calculateSumAndAverage(n, &sum, &average);

    printf("Sum of first %d natural numbers is: %lld\n", n, sum);
    printf("Average of first %d natural numbers is: %.2f\n", n, average);

    return 0;
}