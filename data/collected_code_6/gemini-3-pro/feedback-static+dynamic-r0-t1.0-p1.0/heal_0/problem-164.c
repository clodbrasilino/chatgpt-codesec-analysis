#include <stdio.h>
#include <stdlib.h>

int sum_of_divisors(int n) {
    if (n <= 0) {
        return -1;
    }

    int sum = 0;
    for (int i = 1; i <= n / 2; i++) {
        if (n % i == 0) {
            sum += i;
        }
    }
    return sum;
}

int check_same_divisor_sum(int a, int b) {
    if (a <= 0 || b <= 0) {
        return 0;
    }

    int sum_a = sum_of_divisors(a);
    int sum_b = sum_of_divisors(b);

    if (sum_a == -1 || sum_b == -1) {
        return 0;
    }

    return sum_a == sum_b ? 1 : 0;
}

int main(void) {
    int num1 = 0;
    int num2 = 0;

    if (scanf("%d %d", &num1, &num2) != 2) {
        return EXIT_FAILURE;
    }

    if (check_same_divisor_sum(num1, num2)) {
        printf("The sum of divisors are the same.\n");
    } else {
        printf("The sum of divisors are not the same.\n");
    }

    return EXIT_SUCCESS;
}