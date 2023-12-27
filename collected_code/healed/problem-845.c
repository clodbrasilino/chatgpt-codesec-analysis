#include <stdio.h>
#include <math.h>

int countDigitsInFactorial(int n) {
    if (n < 0) {
        printf("Invalid input. Number must be non-negative.\n");
        return -1;
    }

    if (n <= 1) {
        return 1;
    }

    double digits = 0;
    for (int i = 2; i <= n; i++) {
        digits += log10(i);
    }

    return (int)(digits) + 1;
}

int main() {
    int num = 0;
    printf("Enter a number: ");
    scanf("%d", &num);

    int result = countDigitsInFactorial(num);
    if (result != -1) {
        printf("Number of digits in factorial of %d is %d\n", num, result);
    }

    return 0;
}