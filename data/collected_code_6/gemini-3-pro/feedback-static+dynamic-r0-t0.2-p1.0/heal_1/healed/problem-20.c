#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool is_woodall(unsigned long long n) {
    if (n < 1) {
        return false;
    }

    if (n == 1) {
        return true;
    }

    unsigned long long w = 0;
    unsigned long long i = 1;

    while (w < n) {
        if (i >= 64) {
            break;
        }
        w = i * (1ULL << i) - 1;
        if (w == n) {
            return true;
        }
        i++;
    }

    return false;
}

int main(void) {
    unsigned long long num = 0;
    
    if (scanf("%llu", &num) == 1) {
        if (is_woodall(num)) {
            printf("True\n");
        } else {
            printf("False\n");
        }
        return EXIT_SUCCESS;
    }

    return EXIT_FAILURE;
}