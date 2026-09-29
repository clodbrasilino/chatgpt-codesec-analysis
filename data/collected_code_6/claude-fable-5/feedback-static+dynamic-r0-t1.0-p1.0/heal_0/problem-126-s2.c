#include <stdio.h>
#include <stdlib.h>

static int sum_common_divisors(int a, int b)
{
    int sum = 0;
    int i;
    int min;

    if (a < 0) {
        a = -a;
    }
    if (b < 0) {
        b = -b;
    }
    if (a == 0 || b == 0) {
        return 0;
    }

    min = (a < b) ? a : b;

    for (i = 1; i <= min; i++) {
        if ((a % i == 0) && (b % i == 0)) {
            sum += i;
        }
    }

    return sum;
}

int main(void)
{
    int num1;
    int num2;
    int result;

    printf("Enter first number: ");
    if (scanf("%d", &num1) != 1) {
        fprintf(stderr, "Error: invalid input for first number\n");
        return EXIT_FAILURE;
    }

    printf("Enter second number: ");
    if (scanf("%d", &num2) != 1) {
        fprintf(stderr, "Error: invalid input for second number\n");
        return EXIT_FAILURE;
    }

    result = sum_common_divisors(num1, num2);
    printf("Sum of common divisors of %d and %d is: %d\n", num1, num2, result);

    return EXIT_SUCCESS;
}