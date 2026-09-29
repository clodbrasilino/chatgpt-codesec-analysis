#include <stdio.h>

double geometricSum(int n) {
    double sum = 1.0;

    for (int i = 1; i <= n-1; i++) {
        sum += 1.0 / i;
    }

    return sum;
}

int main() {
    int n = 0;

    printf("Enter a value for n: ");
    if(scanf("%d", &n) != 1) {
        printf("Failed to read integer.\n");
        return 1;
    }

    double result = geometricSum(n);
    printf("Geometric sum of n-1: %.2f\n", result);

    return 0;
}