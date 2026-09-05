#include <stdio.h>
#include <stdbool.h>

bool is_woodall(unsigned long long n) {
    if (n == 0) {
        return false;
    }
    unsigned long long i = 1;
    unsigned long long power = 2;
    unsigned long long result = power * i - 1;
    while (result < n) {
        i++;
        if (__builtin_mul_overflow(power, 2, &power)) {
            break;
        }
        if (__builtin_mul_overflow(power, i, &result)) {
            break;
        }
        result -= 1;
    }
    return result == n;
}

int main(void) {
    unsigned long long num;
    if (scanf("%llu", &num) == 1) {
        if (is_woodall(num)) {
            printf("Yes\n");
        } else {
            printf("No\n");
        }
    }
    return 0;
}