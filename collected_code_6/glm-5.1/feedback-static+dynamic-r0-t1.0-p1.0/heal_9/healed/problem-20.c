#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

bool is_woodall(unsigned long long n) {
    if (n == 0) {
        return false;
    }

    unsigned long long k = 1;
    while (1) {
        if (k > sizeof(unsigned long long) * CHAR_BIT - 1) {
            return false;
        }
        
        unsigned long long power = 1ULL << k;
        
        if (power != 0 && (power - 1) > ULLONG_MAX / k) {
            return false;
        }
        
        unsigned long long term = k * (power - 1);

        if (term == n) {
            return true;
        }

        if (term > n) {
            return false;
        }
        k++;
    }
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