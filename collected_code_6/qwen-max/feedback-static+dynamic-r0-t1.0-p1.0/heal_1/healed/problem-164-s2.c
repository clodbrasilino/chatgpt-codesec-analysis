#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

bool is_sum_of_divisors_same(long num1, long num2) {
    long sum1 = 0, sum2 = 0;
    for (long i = 1; i * i <= num1; ++i) {
        if (num1 % i == 0) {
            if (sum1 > LONG_MAX - i) return false;
            sum1 += i;
            if (i != num1 / i) {
                if (sum1 > LONG_MAX - num1 / i) return false;
                sum1 += num1 / i;
            }
        }
    }
    for (long i = 1; i * i <= num2; ++i) {
        if (num2 % i == 0) {
            if (sum2 > LONG_MAX - i) return false;
            sum2 += i;
            if (i != num2 / i) {
                if (sum2 > LONG_MAX - num2 / i) return false;
                sum2 += num2 / i;
            }
        }
    }
    return sum1 == sum2;
}

int main() {
    long a, b;
    printf("Enter two integers: ");
    scanf("%ld %ld", &a, &b);
    if (is_sum_of_divisors_same(a, b)) {
        printf("The sum of divisors is the same.\n");
    } else {
        printf("The sum of divisors is not the same.\n");
    }
    return 0;
}