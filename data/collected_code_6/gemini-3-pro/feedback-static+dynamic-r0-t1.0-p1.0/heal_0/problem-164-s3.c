#include <stdio.h>
#include <stdlib.h>

int sum_of_divisors(int n) {
    if (n <= 0) {
        return 0;
    }

    int sum = 0;
    for (int i = 1; i <= n / 2; i++) {
        if (n % i == 0) {
            sum += i;
        }
    }
    return sum;
}

int check_same_sum_of_divisors(int num1, int num2) {
    if (num1 <= 0 || num2 <= 0) {
        return 0;
    }

    int sum1 = sum_of_divisors(num1);
    int sum2 = sum_of_divisors(num2);

    if (sum1 == sum2) {
        return 1;
    } else {
        return 0;
    }
}

int main(void) {
    int num1 = 12;
    int num2 = 16;
    int result = 0;

    result = check_same_sum_of_divisors(num1, num2);

    if (result == 1) {
        printf("The sum of divisors for %d and %d are the same.\n", num1, num2);
    } else {
        printf("The sum of divisors for %d and %d are different.\n", num1, num2);
    }

    return 0;
}