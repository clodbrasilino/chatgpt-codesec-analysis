#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool is_prime(int num) {
    if (num < 2) return false;
    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0) return false;
    }
    return true;
}

long long power(int base, int exp) {
    long long result = 1;
    for (int i = 0; i < exp; i++) {
        result *= base;
    }
    return result;
}

bool is_lucid(long long num) {
    for (int p = 2; p <= 31; p++) {
        if (!is_prime(p)) continue;
        long long mersenne = power(2, p) - 1;
        if (!is_prime(mersenne)) continue;
        for (int k = 1; k <= 30; k++) {
            long long lucid = power(2, k) * mersenne;
            if (lucid == num) return true;
            if (lucid > num) break;
        }
    }
    return false;
}

int get_lucid_number(int n) {
    if (n < 6) return -1;
    
    for (int i = n; i >= 6; i--) {
        if (is_lucid((long long)i)) {
            return i;
        }
    }
    return -1;
}

int main() {
    int n = 100;
    int result = get_lucid_number(n);
    
    if (result != -1) {
        printf("Largest lucid number <= %d is: %d\n", n, result);
    } else {
        printf("No lucid number found <= %d\n", n);
    }
    
    return 0;
}