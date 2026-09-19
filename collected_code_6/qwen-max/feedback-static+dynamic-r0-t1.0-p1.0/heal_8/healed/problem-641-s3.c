#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <limits.h>

bool is_safe_multiply(int64_t a, int64_t b, int64_t *result) {
    if (a > 0 && b > 0 && a > (INT64_MAX / b)) return false;
    if (a < 0 && b < 0 && -a > (INT64_MAX / -b) + 1) return false;
    if (a > 0 && b < 0 && a > (INT64_MIN / b)) return false;
    if (a < 0 && b > 0 && b > (INT64_MIN / a)) return false;
    *result = a * b;
    return true;
}

int64_t nth_nonagonal(int64_t n) {
    int64_t temp;
    if (!is_safe_multiply(n, 7, &temp)) return -1;
    temp -= 5 * n;
    if (!is_safe_multiply(temp, n, &temp)) return -1;
    if (temp % 2 != 0) return -1;
    return temp / 2;
}

int main() {
    int64_t n;
    printf("Enter the value of n: ");
    if (scanf("%ld", &n) != 1) {
        fprintf(stderr, "Invalid input.\n");
        return 1;
    }
    if (n <= 0) {
        fprintf(stderr, "n must be a positive integer.\n");
        return 1;
    }
    int64_t nonagonal_number = nth_nonagonal(n);
    if (nonagonal_number == -1) {
        fprintf(stderr, "Integer overflow detected.\n");
        return 1;
    }
    printf("The %ldth nonagonal number is: %ld\n", n, nonagonal_number);
    return 0;
}