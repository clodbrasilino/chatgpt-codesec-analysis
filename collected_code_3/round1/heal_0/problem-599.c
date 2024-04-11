#include <stdio.h>

void findSumAndAverage(int n, int *sum, float *average) {
    *sum = n * (n + 1) / 2;
    *average = (float)*sum / n;
}

int main() {
    int n, sum;
    float average;

    printf("Enter a number: ");
    scanf("%d", &n);

    findSumAndAverage(n, &sum, &average);

    printf("Sum = %d, Average = %.2f\n", sum, average);

    return 0;
}