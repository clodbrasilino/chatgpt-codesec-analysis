#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool is_woodall(unsigned long long n) {
    if (n < 1) {
        return false;
    }

    if (n % 2 == 0) {
        return false;
    }

    unsigned long long w = n + 1;

    for (unsigned long long k = 1; k < 64; k++) {
        unsigned long long val = k * (1ULL << k);
        if (val == w) {
            return true;
        }
        if (val > w) {
            break;
        }
    }

    return false;
}

int main(void) {
    unsigned long long num = 0;
    
    if (scanf("%llu", &num) != 1) {
        return EXIT_FAILURE;
    }

    if (is_woodall(num)) {
        printf("1\n");
    } else {
        printf("0\n");
    }

    return EXIT_SUCCESS;
}