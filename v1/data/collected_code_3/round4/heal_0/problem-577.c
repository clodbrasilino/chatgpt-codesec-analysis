#include <stdio.h>

int lastDigitInFactorial(int n) {
    if (n >= 5)
        return 0;

    int res = 1;
    for (int i = 1; i <= n; i++)
        res *= i;

    return res % 10;
}

int main() {
    int num;
    printf("Enter a number: ");
    scanf("%d", &num);
    printf("Last digit in factorial of %d is %d\n", num, lastDigitInFactorial(num));
    return 0;
}