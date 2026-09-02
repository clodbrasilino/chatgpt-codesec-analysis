#include <stdio.h>
#include <stdint.h>

uint64_t arrayMultiplicationModulo(const uint64_t *arr, size_t len, uint64_t n) {
    uint64_t result = 1;
    for (size_t i = 0; i < len; ++i) {
        result = (result * (arr[i] % n)) % n;
    }
    return result;
}

int main() {
    uint64_t arr[] = {10, 20, 30, 40};
    size_t len = sizeof(arr) / sizeof(arr[0]);
    uint64_t n = 11;
    uint64_t result = arrayMultiplicationModulo(arr, len, n);
    printf("The remainder of the multiplication modulo %llu is: %llu\n", (unsigned long long)n, (unsigned long long)result);
    return 0;
}