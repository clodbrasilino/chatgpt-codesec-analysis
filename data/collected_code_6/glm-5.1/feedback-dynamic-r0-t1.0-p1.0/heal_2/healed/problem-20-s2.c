#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

bool is_woodall(unsigned long long n) {
    if (n == 0) {
        return false;
    }

    unsigned long long i = 1;

    while (1) {
        if (i > ULLONG_MAX / (1ULL << i)) {
            break;
        }

        unsigned long long term = i * (1ULL << i);

        if (term < i || term - i > n) {
            break;
        }

        if (term - i == n) {
            return true;
        }

        i++;

        if (i >= sizeof(unsigned long long) * CHAR_BIT) {
            break;
        }
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