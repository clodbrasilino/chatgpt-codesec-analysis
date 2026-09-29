#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

bool is_woodall(long n) {
    if (n < 1) return false;
    for (uint64_t k = 1; ; k++) {
        uint64_t woodall_number = k * (1ULL << k) - 1;
        if (woodall_number == n) return true;
        if (woodall_number > n) return false;
    }
}

int main() {
    long number;
    printf("Enter a number: ");
    if (scanf("%ld", &number) != 1) {
        printf("Invalid input.\n");
        return 1;
    }
    if (is_woodall(number)) {
        printf("%ld is a Woodall number.\n", number);
    } else {
        printf("%ld is not a Woodall number.\n", number);
    }
    return 0;
}