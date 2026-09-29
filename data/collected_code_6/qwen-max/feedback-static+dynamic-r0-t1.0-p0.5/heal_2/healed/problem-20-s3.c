#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <inttypes.h>

bool is_woodall_number(long n) {
    if (n < 1) return false;
    for (uint64_t k = 1; ; k++) {
        if (k > 62) break;
        uint64_t woodall = k * ((uint64_t)1 << k) - 1;
        if (woodall > LONG_MAX) break;
        if (woodall == n) return true;
        if (woodall > n) return false;
    }
}

int main() {
    long number;
    printf("Enter a number: ");
    if (scanf("%ld", &number) != 1) {
        printf("Invalid input.\n");
        return 1;
    }
    if (is_woodall_number(number)) {
        printf("%ld is a Woodall number.\n", number);
    } else {
        printf("%ld is not a Woodall number.\n", number);
    }
    return 0;
}