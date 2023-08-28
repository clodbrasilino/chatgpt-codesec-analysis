#include <stdio.h>

double harmonicSum(int n) {
    double sum = 0.0;
    for (int i = 1; i <= n-1; i++) {
        sum += 1.0 / i;
    }
    return sum;
}

int main() {
    int n = 5;
    double result = harmonicSum(n);
    printf("Harmonic sum of %d-1 = %lf \n", n, result);
    return 0;
}