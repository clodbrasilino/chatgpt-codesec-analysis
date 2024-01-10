#include <stdio.h>

int calculateSumOfSeries(int n) {
    int sum = 0;

    for (int i = 1; i <= n; i++) {
        sum += i * i;
    }

    return sum;
}

int main() {
    int n;
    n = 0;
    printf("Enter the value of n: ");
    scanf("%d", &n);
    printf("Sum of series: %d", calculateSumOfSeries(n));

    return 0;
}