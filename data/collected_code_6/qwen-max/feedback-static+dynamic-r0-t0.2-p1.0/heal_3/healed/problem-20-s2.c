#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
#include <inttypes.h>
#include <stdint.h>

bool is_woodall_number(uint64_t n) {
    if (n == 0) return false;
    for (uint64_t k = 1; ; k++) {
        uint64_t woodall;
        if (k >= 63 || (woodall = k * (1ULL << k) - 1) > n) break;
        if (woodall == n) return true;
    }
    return false;
}

int main() {
    long number;
    printf("Enter a number: ");
    scanf("%ld", &number);
    if (is_woodall_number(number)) {
        printf("%ld is a Woodall number.\n", number);
    } else {
        printf("%ld is not a Woodall number.\n", number);
    }
    return 0;
}