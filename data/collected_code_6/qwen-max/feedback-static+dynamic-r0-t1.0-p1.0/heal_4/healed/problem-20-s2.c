#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <limits.h>

bool is_woodall(uint64_t n) {
    for (uint64_t k = 1; ; ++k) {
        if (k > 63) break; // Prevent overflow by limiting k
        uint64_t woodall_number = k * (1ULL << k) - 1;
        if (woodall_number == n) return true;
        if (woodall_number > n) break;
    }
    return false;
}

int main() {
    uint64_t number;
    printf("Enter a number: ");
    if (scanf("%lu", &number) != 1) {
        printf("Invalid input\n");
        return 1;
    }

    if (is_woodall(number)) {
        printf("%lu is a Woodall number.\n", number);
    } else {
        printf("%lu is not a Woodall number.\n", number);
    }

    return 0;
}