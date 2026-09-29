#include <stdio.h>

void calculateSumAndAverage(int n, int *sum, float *average) {
    *sum = 0;
    for (int i = 1; i <= n; i++) {
        *sum += i;
    }
    if (n > 0) {
        *average = (float)*sum / n;
    } else {
        *average = 0.0f;
    }
}

int main() {
    int n;
    printf("Enter the value of n: ");
    scanf("%d", &n);

    int sum;
    float average;
    calculateSumAndAverage(n, &sum, &average);

    printf("Sum of first %d natural numbers is %d\n", n, sum);
    printf("Average of first %d natural numbers is %.2f\n", n, average);

    return 0;
}