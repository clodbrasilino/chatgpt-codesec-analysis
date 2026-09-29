#include <stdio.h>

int lastDigitOfFactorialDivision(int a, int b) {
    if (a < b) {
        return 0;
    } else if (a == b) {
        return 1;
    } else {
        return 0;
    }
}

int main() {
    int a, b;
    printf("Enter two numbers: ");
    scanf("%d %d", &a, &b);
    int result = lastDigitOfFactorialDivision(a, b);
    printf("The last digit when factorial of %d divides factorial of %d is %d\n", a, b, result);
    return 0;
}