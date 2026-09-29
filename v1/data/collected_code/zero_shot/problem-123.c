#include <stdio.h>

int sum_divisors(int n) {
    int sum = 0;
    for (int i = 1; i <= n / 2; i++) {
        if (n % i == 0) {
            sum += i;
        }
    }
    return sum;
}

int is_amicable(int n) {
    int sum_n = sum_divisors(n);
    int sum_sum_n = sum_divisors(sum_n);

    if (n == sum_sum_n && n != sum_n) {
        return 1;
    } else {
        return 0;
    }
}

int sum_amicable(int n) {
    int sum = 0;
    for (int i = 1; i <= n; i++) {
        if (is_amicable(i)) {
            sum += i;
        }
    }
    return sum;
}

int main() {
    int num;
    printf("Enter a number: ");
    scanf("%d", &num);

    int result = sum_amicable(num);
    printf("Sum of amicable numbers: %d\n", result);

    return 0;
}