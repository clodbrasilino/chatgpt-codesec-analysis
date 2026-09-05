#include <stdio.h>
#include <limits.h>

unsigned long smallest_prime_divisor(unsigned long n) {
    if (n <= 1) {
        return 0;
    }
    if (n % 2 == 0) {
        return 2;
    }
    for (unsigned long i = 3; i * i <= n; i += 2) {
        if (n % i == 0) {
            return i;
        }
    }
    return n;
}

int main(void) {
    unsigned long num;
    if (scanf("%lu", &num) != 1) {
        return 1;
    }
    unsigned long result = smallest_prime_divisor(num);
    if (result == 0) {
        return 1;
    }
    printf("%lu\n", result);
    return 0;
}