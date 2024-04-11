#include <stdio.h>

double power(double a, int b) {
    double result = 1.0;
    for(int i = 0; i < b; i++) {
        result *= a;
    }
    return result;
}

int main() {
    double a;
    int b;
    printf("Enter base: ");
    scanf("%lf", &a);
    printf("Enter exponent: ");
    scanf("%d", &b);
    printf("Result: %.2lf\n", power(a, b));
    return 0;
}