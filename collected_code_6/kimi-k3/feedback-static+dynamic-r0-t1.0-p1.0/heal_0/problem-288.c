#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

static uint64_t mod_mul(uint64_t a, uint64_t b, uint64_t p) {
    uint64_t result = 0;
    a %= p;
    b %= p;
    while (b > 0) {
        if (b & 1) {
            result = (result + a) % p;
        }
        b >>= 1;
        if (b > 0) {
            a = (a * 2) % p;
        }
    }
    return result;
}

static int is_prime(uint64_t n) {
    if (n < 2) {
        return 0;
    }
    if (n == 2 || n == 3) {
        return 1;
    }
    if (n % 2 == 0 || n % 3 == 0) {
        return 0;
    }
    for (uint64_t i = 5; i <= n / i; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) {
            return 0;
        }
    }
    return 1;
}

size_t count_self_inverse(const uint64_t *arr, size_t n, uint64_t p) {
    if (arr == NULL || n == 0 || p < 2 || !is_prime(p)) {
        return 0;
    }
    
    size_t count = 0;
    for (size_t i = 0; i < n; i++) {
        uint64_t a = arr[i] % p;
        if (a == 1 || a == p - 1) {
            count++;
        }
    }
    return count;
}

int main(void) {
    uint64_t arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    size_t n = sizeof(arr) / sizeof(arr[0]);
    uint64_t p = 13;
    
    size_t result = count_self_inverse(arr, n, p);
    printf("%zu\n", result);
    
    return 0;
}