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

long long sum_of_primes(int n) {
    long long sum = 0;
    for (int i = 1; i <= n; i++) {
        if (is_prime(i)) {
            sum += i;
        }
    }
    return sum;
}

int main(void) {
    int n;
    if (scanf("%d", &n) != 1 || n < 1) {
        fprintf(stdout, "%lld\n", 0LL);
        return 0;
    }
    long long result = sum_of_primes(n);
    printf("%lld\n", result);
    return 0;
}