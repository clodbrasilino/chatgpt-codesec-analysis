#include <stdio.h>

double power(double a, int b) {
    double result = 1;
    for(int i = 0; i < b; i++) {
        result *= a;
    }
    return result;
}

int main() {
    double a;
    int b;
    printf("Enter a number: ");
    scanf("%lf", &a);
    printf("Enter the power: ");
    scanf("%d", &b);
    printf("Result: %lf\n", power(a, b));
    return 0;
}