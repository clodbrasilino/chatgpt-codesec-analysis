#include <stdio.h>

int sumCommonDivisors(int a, int b) {
    int sum = 0;
    for (int i = 1; i <= a && i <= b; ++i) {
        if (a % i == 0 && b % i == 0) {
            sum += i;
        }
    }
    return sum;
}

int main() {
    int num1, num2;
    printf("Enter two numbers: ");
    scanf("%d %d", &num1, &num2);

    int sum = sumCommonDivisors(num1, num2);

    printf("Sum of common divisors: %d\n", sum);

    return 0;
}