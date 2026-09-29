#include <stdio.h>
#include <stdbool.h>

bool is_woodall(unsigned long long n) {
    if (n == 0) {
        return false;
    }
    unsigned long long i = 1;
    unsigned long long power = 1;
    while (power != 0) {
        unsigned long long woodall = i * power - 1;
        if (woodall == n) {
            return true;
        }
        if (woodall > n) {
            return false;
        }
        i++;
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