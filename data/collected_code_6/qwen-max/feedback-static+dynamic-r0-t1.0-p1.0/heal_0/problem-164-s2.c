#include <stdio.h>
#include <stdbool.h>

bool is_sum_of_divisors_same(int num1, int num2) {
    int sum1 = 0, sum2 = 0;
    for (int i = 1; i * i <= num1; ++i) {
        if (num1 % i == 0) {
            sum1 += i;
            if (i != num1 / i) {
                sum1 += num1 / i;
            }
        }
    }
    for (int i = 1; i * i <= num2; ++i) {
        if (num2 % i == 0) {
            sum2 += i;
            if (i != num2 / i) {
                sum2 += num2 / i;
            }
        }
    }
    return sum1 == sum2;
}

int main() {
    int a, b;
    printf("Enter two integers: ");
    scanf("%d %d", &a, &b);
    if (is_sum_of_divisors_same(a, b)) {
        printf("The sum of divisors is the same.\n");
    } else {
        printf("The sum of divisors is not the same.\n");
    }
    return 0;
}