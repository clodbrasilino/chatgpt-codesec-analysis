#include<stdio.h>

int factorial(int n) {
    if (n == 0 || n == 1) {
        return 1;
    } else {
        return n * factorial(n - 1);
    }
}

int lastDigitFactorialDivides(int a, int b) {
    int factorialOfA = factorial(a);
    int factorialOfB = factorial(b);

    int lastDigitOfA = factorialOfA % 10;
    int lastDigitOfB = factorialOfB % 10;

    if (lastDigitOfA == 0 || lastDigitOfB == 0) {
        return 0;
    }

    if (lastDigitOfA == lastDigitOfB) {
        return 1;
    }

    return 0;
}

int main() {
    int a, b;
    printf("Enter the values of a and b: ");
    scanf("%d %d", &a, &b);

    int result = lastDigitFactorialDivides(a, b);

    if (result == 1) {
        printf("Last digit of factorial of a divides factorial of b.\n");
    } else {
        printf("Last digit of factorial of a does not divide factorial of b.\n");
    }

    return 0;
}