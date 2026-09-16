#include <stdio.h>
#include <stdbool.h>
#include <math.h>

bool is_prime(int n) {
    if (n <= 1) return false;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) return false;
    }
    return true;
}

int count_distinct_prime_powers(int number) {
    int count = 0;
    for (int i = 2; i <= sqrt(number); i++) {
        if (number % i == 0 && is_prime(i)) {
            int power = 0;
            while (number % i == 0) {
                number /= i;
                power++;
            }
            count++;
            if (power > 1) count += power - 1;
        }
    }
    if (number > 1 && is_prime(number)) count++;
    return count;
}

int main() {
    int number;
    printf("Enter a number: ");
    scanf("%d", &number);
    int result = count_distinct_prime_powers(number);
    printf("Number of distinct prime powers: %d\n", result);
    return 0;
}