#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

bool is_woodall(unsigned long long n) {
    if (n == 0) {
        return false;
    }

    unsigned long long w = 1;
    unsigned long long i = 1;

    while (w <= n) {
        if (w == n) {
            return true;
        }
        i++;
        
        if (i >= sizeof(unsigned long long) * CHAR_BIT || (1ULL << i) > ULLONG_MAX / i) {
            break;
        }
        
        w = i * (1ULL << i) - i;
    }

    return false;
}

int main(void) {
    unsigned long long num;

    if (scanf("%llu", &num) != 1) {
        return 1;
    }

    if (is_woodall(num)) {
        printf("Yes\n");
    } else {
        printf("No\n");
    }

    return 0;
}