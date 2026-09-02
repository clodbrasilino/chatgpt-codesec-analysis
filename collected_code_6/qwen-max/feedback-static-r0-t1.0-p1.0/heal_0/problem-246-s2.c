#include <stdio.h>
#include <math.h>

double babylonian_sqrt(double n) {
    double x = n;
    double y = 1.0;
    double epsilon = 1e-7;
    while (x - y > epsilon) {
        x = (x + y) / 2;
        y = n / x;
    }
    return x;
}

int main() {
    double n;
    printf("Enter a number: ");
    if (scanf("%lf", &n) != 1 || n < 0) {
        printf("Invalid input.\n");
        return 1;
    }
    double result = babylonian_sqrt(n);
    printf("Square root of %.2lf is %.2lf\n", n, result);
    return 0;
}