#include <stdio.h>
#include <math.h>
#include <stdint.h>
#include <limits.h>

double geometric_sum(int n) {
    if (n < 0 || n > 50) {
        return 0.0;
    }
    if (n == 0) {
        return 1.0;
    } else {
        double result = 1.0, term = 1.0;
        for (int i = 1; i <= n; ++i) {
            term /= 2.0;
            result += term;
        }
        return result;
    }
}

int main() {
    int n;
    printf("Enter an integer: ");
    if (scanf("%d", &n) != 1) {
        printf("Invalid input.\n");
        return 1;
    }
    printf("Geometric sum of %d is: %lf\n", n, geometric_sum(n));
    return 0;
}