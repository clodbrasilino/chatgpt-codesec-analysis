#include <stdio.h>

double sqrtBabylonian(double n) {
    double x = n;
    double y = 1;
    double e = 0.000001;
    while (x - y > e) {
        x = (x + y) / 2;
        y = n / x;
    }
    return x;
}

int main() {
    double n = 50;
    printf("Square root of %lf is %lf", n, sqrtBabylonian(n));
    return 0;
}