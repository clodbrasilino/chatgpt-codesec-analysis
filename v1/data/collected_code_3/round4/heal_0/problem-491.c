#include <stdio.h>
#include <math.h>

double sumOfGP(double a, double r, int n) {
    double sum = 0.0;
    for (int i = 0; i < n; i++) {
        sum += a * pow(r, i);
    }
    return sum;
}

int main() {
    double a = 1.0;
    double r = 0.5;
    int n = 10;

    double sum = sumOfGP(a, r, n);

    printf("Sum of geometric progression series is: %.2f\n", sum);

    return 0;
}