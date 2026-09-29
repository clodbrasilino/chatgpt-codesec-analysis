#include <stdio.h>

int sumOfDivisors(int n) {
    int sum = 0;
    for (int i = 1; i <= n; i++) {
        if (n % i == 0) {
            sum += i;
        }
    }
    return sum;
}

int checkSumOfDivisors(int a, int b) {
    return sumOfDivisors(a) == sumOfDivisors(b);
}

int main() {
    int num1, num2;
    printf("Enter two numbers: ");
    scanf("%d %d", &num1, &num2);

    if (checkSumOfDivisors(num1, num2)) {
        printf("Sum of divisors are same\n");
    } else {
        printf("Sum of divisors are not same\n");
    }

    return 0;
}