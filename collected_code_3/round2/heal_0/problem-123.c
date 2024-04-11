#include <stdio.h>

int sum_of_divisors(int n) {
    int sum = 1;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            if (i * i != n)
                sum = sum + i + n / i;
            else
                sum = sum + i;
        }
    }
    return sum;
}

int sum_of_amicable_numbers(int n) {
    int sum = 0;
    for (int i = 1; i <= n; i++) {
        int sum1 = sum_of_divisors(i);
        if (sum1 > i) {
            if (sum_of_divisors(sum1) == i)
                sum += i + sum1;
        }
    }
    return sum;
}

int main() {
    int n;
    printf("Enter a number: ");
    scanf("%d", &n);
    printf("Sum of all amicable numbers from 1 to %d is %d\n", n, sum_of_amicable_numbers(n));
    return 0;
}