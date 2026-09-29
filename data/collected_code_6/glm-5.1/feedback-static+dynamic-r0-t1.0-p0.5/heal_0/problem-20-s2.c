#include <stdio.h>
#include <stdbool.h>

bool is_woodall(unsigned long long n) {
    if (n == 0) {
        return false;
    }
    unsigned long long i = 1;
    unsigned long long val = 1;
    while (val < n) {
        i++;
        if (i > ULLONG_MAX / 2) {
            break;
        }
        val = i * 2 * i - 1;
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