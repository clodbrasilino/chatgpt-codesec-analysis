#include <stdio.h>
#include <stdbool.h>

bool is_prime(int num) {
    if (num <= 1) {
        return false;
    }
    if (num == 2 || num == 3) {
        return true;
    }
    if (num % 2 == 0 || num % 3 == 0) {
        return false;
    }
    for (int i = 5; i * i <= num; i += 6) {
        if (num % i == 0 || num % (i + 2) == 0) {
            return false;
        }
    }
    return true;
}

unsigned long long sum_of_primes(int n) {
    if (n < 2) {
        return 0;
    }
    unsigned long long sum = 0;
    for (int i = 2; i <= n; i++) {
        if (is_prime(i)) {
            sum += (unsigned long long)i;
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