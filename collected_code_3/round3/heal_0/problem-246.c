#include <stdio.h>

double sqrtBabylonian(double num) {
    double x = num;
    double y = 1;
    double e = 0.000001;
    
    while(x - y > e) {
        x = (x + y) / 2;
        y = num / x;
    }
    return x;
}

int main() {
    double num = 16;
    printf("Square root of %lf is %lf", num, sqrtBabylonian(num));
    return 0;
}