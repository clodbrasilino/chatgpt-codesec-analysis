#include <stdio.h>

double babylonianSqrt(double num) {
    double x = num;
    double y = 1;
    double e = 0.000001;

    while (x - y > e) {
        x = (x + y) / 2;
        y = num / x;
    }

    return x;
}

int main() {
    double num = 50;
    printf("Square root of %f is %f", num, babylonianSqrt(num));
    return 0;
}