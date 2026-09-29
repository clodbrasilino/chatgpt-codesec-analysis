#include <stdio.h>
#include <stdbool.h>

bool is_woodall(unsigned long long n) {
    if (n == 0) {
        return false;
    }
    unsigned long long power = 1;
    while (power != 0) {
        if (n % power == power - 1) {
            unsigned long long i = (n + 1) / power;
            if (i >= 1 && i * power - 1 == n) {
                return true;
            }
        }
        power *= 2;
    }
    return false;
}

int main(void) {
    unsigned long long num;
    if (scanf("%llu", &num) == 1) {
        if (is_woodall(num)) {
            printf("YES\n");
        } else {
            printf("NO\n");
        }
    }
    return 0;
}