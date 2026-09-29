#include <stdio.h>
#include <math.h>

double sqrt_babylonian(double n) {
    double x = n;
    double y = 1.0;
    double e = 0.0000001;
    while (x - y > e) {
        x = (x + y) / 2;
        y = n / x;
    }
    return x;
}

int main() {
    double n;
    printf("Enter a number: ");
    if (scanf("%lf", &n) == 1 && n >= 0) {
        double result = sqrt_babylonian(n);
        printf("The square root of %.2f is %.6f\n", n, result);
    } else {
        printf("Invalid input.\n");
    }
    return 0;
}