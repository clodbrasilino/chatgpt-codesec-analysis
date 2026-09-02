#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int sum_digits(int a, int b) {
    int sum = a + b;
    return (sum == 0) ? 1 : (int)log10(abs(sum)) + 1;
}

int main() {
    int num1 = 123;
    int num2 = 777;

    int digits = sum_digits(num1, num2);
    printf("The number of digits in the sum is: %d\n", digits);

    return 0;
}