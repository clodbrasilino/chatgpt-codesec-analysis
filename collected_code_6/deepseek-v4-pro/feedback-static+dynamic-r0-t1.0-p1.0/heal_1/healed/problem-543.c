#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

int count_digits(int sum) {
    int count = 0;
    if (sum == 0) {
        return 1;
    }
    if (sum < 0) {
        if (sum == INT_MIN) {
            return count_digits(INT_MAX) + 1;
        }
        sum = -sum;
    }
    while (sum > 0) {
        sum /= 10;
        count++;
    }
    return count;
}

int add_numbers(int a, int b) {
    if ((b > 0) && (a > INT_MAX - b)) {
        printf("Overflow detected.\n");
        exit(1);
    }
    if ((b < 0) && (a < INT_MIN - b)) {
        printf("Underflow detected.\n");
        exit(1);
    }
    return a + b;
}

int main(void) {
    int num1 = 0;
    int num2 = 0;
    int sum = 0;

    printf("Enter first number: ");
    if (scanf("%d", &num1) != 1) {
        printf("Invalid input.\n");
        return 1;
    }

    printf("Enter second number: ");
    if (scanf("%d", &num2) != 1) {
        printf("Invalid input.\n");
        return 1;
    }

    sum = add_numbers(num1, num2);
    printf("Sum: %d\n", sum);
    printf("Number of digits in sum: %d\n", count_digits(sum));

    return 0;
}