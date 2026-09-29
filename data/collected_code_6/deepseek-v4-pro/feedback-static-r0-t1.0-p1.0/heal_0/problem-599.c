#include <stdio.h>

void calculate_sum_and_average(int n, long long *sum, double *average) {
    *sum = 0;
    for (int i = 1; i <= n; i++) {
        *sum += i;
    }
    *average = (double)*sum / n;
}

int main(void) {
    int n;
    printf("Enter a positive integer: ");
    if (scanf("%d", &n) != 1) {
        printf("Invalid input.\n");
        return 1;
    }
    if (n <= 0) {
        printf("Please enter a positive integer.\n");
        return 1;
    }
    long long sum;
    double average;
    calculate_sum_and_average(n, &sum, &average);
    printf("Sum = %lld\n", sum);
    printf("Average = %.2f\n", average);
    return 0;
}