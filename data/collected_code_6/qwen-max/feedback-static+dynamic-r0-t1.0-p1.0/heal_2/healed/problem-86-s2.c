#include <stdio.h>
#include <stdint.h>
#include <limits.h>

int64_t nth_centered_hexagonal(int64_t n) {
    if (n > 0x1FFFFFFFFFFFFFFFLL || n < -0x1FFFFFFFFFFFFFFFLL) {
        fprintf(stderr, "Input out of range\n");
        return -1;
    }
    int64_t temp = 3 * n * (n - 1);
    if (temp < 0 || (INT64_MAX - 1 < temp)) {
        fprintf(stderr, "Overflow detected\n");
        return -1;
    }
    return temp + 1;
}

int main() {
    int64_t n;
    printf("Enter the value of n: ");
    if (scanf("%ld", &n) != 1) {
        fprintf(stderr, "Input error\n");
        return 1;
    }
    int64_t result = nth_centered_hexagonal(n);
    if (result == -1) {
        return 1;
    }
    printf("The %ldth centered hexagonal number is: %ld\n", n, result);
    return 0;
}