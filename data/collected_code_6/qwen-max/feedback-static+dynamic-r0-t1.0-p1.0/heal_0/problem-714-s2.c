#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool is_prime(int n) {
    if (n <= 1) return false;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) return false;
    }
    return true;
}

int count_distinct_prime_powers(long long n) {
    int count = 0;
    for (int i = 2; n > 1; i++) {
        if (is_prime(i)) {
            int power = 0;
            while (n % i == 0) {
                n /= i;
                power++;
            }
            if (power > 0) {
                count++;
            }
        }
    }
    return count;
}

int main() {
    long long number;
    printf("Enter a number: ");
    if (scanf("%lld", &number) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    int result = count_distinct_prime_powers(number);
    printf("Number of distinct prime powers: %d\n", result);
    return EXIT_SUCCESS;
}