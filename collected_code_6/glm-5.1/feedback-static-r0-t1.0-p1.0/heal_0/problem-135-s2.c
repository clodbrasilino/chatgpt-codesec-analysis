#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

bool nth_hexagonal_number(unsigned long long n, unsigned long long *result) {
    if (result == NULL) {
        return false;
    }
    if (n == 0) {
        return false;
    }
    unsigned long long limit = ULLONG_MAX / 2ULL;
    if (n > limit) {
        return false;
    }
    *result = n * (2ULL * n - 1ULL);
    return true;
}

int main(void) {
    unsigned long long n;
    unsigned long long result;
    if (scanf("%llu", &n) != 1) {
        return 1;
    }
    if (nth_hexagonal_number(n, &result)) {
        printf("%llu\n", result);
        return 0;
    }
    return 1;
}