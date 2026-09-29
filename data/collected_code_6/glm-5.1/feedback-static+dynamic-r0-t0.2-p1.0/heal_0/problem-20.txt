#include <stdio.h>
#include <stdbool.h>

bool is_woodall(unsigned long long n) {
    if (n == 0) {
        return false;
    }
    unsigned long long i = 1;
    unsigned long long val = 1;
    while (val < n) {
        if (i > ULLONG_MAX / 2) {
            return false;
        }
        i++;
        if (i > ULLONG_MAX / i) {
            return false;
        }
        val = i * i;
        if (val > ULLONG_MAX - i) {
            return false;
        }
        val += i;
        val--;
    }
    return val == n;
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