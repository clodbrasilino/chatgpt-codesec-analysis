#include <stdio.h>

int factorial(int n) {
    int fact = 1;
    for(int i = 1; i <= n; i++) {
        fact *= i;
    }
    return fact;
}

int lastDigit(int a, int b) {
    int factA = factorial(a);
    int factB = factorial(b);
    int result = factA / factB;
    return result % 10;
}

int main() {
    int a = 5;
    int b = 3;
    int digit = lastDigit(a, b);
    printf("The last digit when factorial of %d divides factorial of %d is %d\n", a, b, digit);
    return 0;
}