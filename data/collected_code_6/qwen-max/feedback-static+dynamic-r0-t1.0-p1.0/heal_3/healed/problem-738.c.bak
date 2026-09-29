#include <stdio.h>
#include <math.h>
#include <limits.h>

double geometric_sum(int n) {
    if (n < 0) {
        return 0;
    }
    double sum = 0;
    for (int i = 0; i <= n; i++) {
        sum += 1.0 / pow(2, i);
    }
    return sum;
}

int main() {
    int n;
    printf("Enter an integer: ");
    scanf("%d", &n);
    if (n >= 0 && n <= INT_MAX) {
        printf("Geometric sum of %d is: %.15lf\n", n, geometric_sum(n));
    } else {
        printf("Invalid input. Please enter a non-negative integer.\n");
    }
    return 0;
}