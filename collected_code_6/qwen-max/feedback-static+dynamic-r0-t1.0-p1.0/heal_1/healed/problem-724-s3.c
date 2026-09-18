#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>

int sum_of_digits(long long num) {
    int sum = 0;
    while (num > 0) {
        sum += num % 10;
        num /= 10;
    }
    return sum;
}

int main() {
    int base, exp;
    printf("Enter base and exponent: ");
    if (scanf("%d %d", &base, &exp) != 2) {
        fprintf(stderr, "Invalid input.\n");
        return EXIT_FAILURE;
    }

    long long result;
    if (exp >= 0 && (exp == 0 || (LLONG_MAX / base >= pow(base, exp - 1)))) {
        result = pow(base, exp);
        int sum = sum_of_digits(result);
        printf("Sum of digits: %d\n", sum);
    } else {
        fprintf(stderr, "Result is out of range for long long.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}