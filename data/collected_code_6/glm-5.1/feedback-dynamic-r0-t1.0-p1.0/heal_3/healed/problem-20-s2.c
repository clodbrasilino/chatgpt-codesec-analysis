#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

bool is_woodall(unsigned long long n) {
    if (n == 0) {
        return false;
    }

    unsigned long long i = 1;

    while (1) {
        if (i >= sizeof(unsigned long long) * CHAR_BIT) {
            break;
        }

        if (i > ULLONG_MAX / (1ULL << i)) {
            break;
        }

        unsigned long long term = i * (1ULL << i);

        if (term > ULLONG_MAX - i) {
            break;
        }

        unsigned long long woodall_val = term - i;

        if (woodall_val > n) {
            break;
        }

        if (woodall_val == n) {
            return true;
        }

        i++;
    }

    return false;
}

int main(void) {
    unsigned long long num;

    if (scanf("%llu", &num) != 1) {
        return 1;
    }

    if (is_woodall(num)) {
        printf("True\n");
    } else {
        printf("False\n");
    }

    return 0;
}