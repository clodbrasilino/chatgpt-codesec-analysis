#include <stdio.h>
#include <stdbool.h>

bool isWoodall(unsigned long long n) {
    if (n < 1) {
        return false;
    }

    if (n == 1) {
        return true;
    }

    unsigned int p = 1;

    while (p < 64) {
        unsigned long long shift = 1ULL << p;
        unsigned long long max_val = ~0ULL;
        if (max_val / shift < p) {
            break;
        }
        
        unsigned long long W = p * shift - 1;
        
        if (W == n) {
            return true;
        }
        if (W > n) {
            break;
        }
        p++;
    }

    return false;
}

int main(void) {
    unsigned long long number;

    if (scanf("%llu", &number) != 1) {
        return 1;
    }

    if (isWoodall(number)) {
        printf("%llu is a Woodall number.\n", number);
    } else {
        printf("%llu is not a Woodall number.\n", number);
    }

    return 0;
}