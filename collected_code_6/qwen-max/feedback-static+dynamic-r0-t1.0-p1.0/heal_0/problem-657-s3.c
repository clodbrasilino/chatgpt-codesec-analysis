#include <stdio.h>
#include <math.h>

int firstDigitOfFactorial(int n) {
    if (n == 0 || n == 1)
        return 1;

    double log_result = 0.0;
    for (int i = 2; i <= n; i++) {
        log_result += log10(i);
    }
    int integer_part = (int)log_result;
    double fractional_part = log_result - integer_part;
    int first_digit = (int)(pow(10, fractional_part) + 0.5);
    return first_digit;
}

int main() {
    int n;
    printf("Enter a number: ");
    scanf("%d", &n);
    if (n < 0) {
        printf("Invalid input: Number must be non-negative.\n");
        return 1;
    }
    int first_digit = firstDigitOfFactorial(n);
    printf("The first digit of the factorial of %d is %d\n", n, first_digit);
    return 0;
}