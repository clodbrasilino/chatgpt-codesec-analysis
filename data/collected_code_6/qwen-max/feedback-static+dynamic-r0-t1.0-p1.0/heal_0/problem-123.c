#include <stdio.h>
#include <stdlib.h>

int sum_of_divisors(int n) {
    int sum = 1;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            sum += i;
            if (i != n / i) {
                sum += n / i;
            }
        }
    }
    return sum;
}

int is_amicable(int a, int b) {
    return (sum_of_divisors(a) == b && sum_of_divisors(b) == a && a != b);
}

int sum_amicable_numbers(int limit) {
    int sum = 0;
    for (int i = 2; i < limit; i++) {
        int div_sum = sum_of_divisors(i);
        if (div_sum > i && div_sum < limit && is_amicable(i, div_sum)) {
            sum += i + div_sum;
        }
    }
    return sum;
}

int main() {
    int limit = 10000;
    printf("Sum of all amicable numbers from 1 to %d: %d\n", limit, sum_amicable_numbers(limit));
    return 0;
}