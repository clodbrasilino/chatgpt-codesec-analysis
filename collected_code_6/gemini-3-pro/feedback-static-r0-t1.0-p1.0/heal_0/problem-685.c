#include <stdio.h>
#include <stdbool.h>

bool is_prime(int num) {
    if (num <= 1) {
        return false;
    }
    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0) {
            return false;
        }
    }
    return true;
}

unsigned long long sum_of_primes(int n) {
    unsigned long long sum = 0;
    for (int i = 1; i <= n; i++) {
        if (is_prime(i)) {
            sum += i;
        }
    }
    return sum;
}

int main(void) {
    int n;
    
    if (scanf("%d", &n) != 1) {
        return 1;
    }

    if (n < 1) {
        return 1;
    }

    unsigned long long result = sum_of_primes(n);
    printf("%llu\n", result);

    return 0;
}