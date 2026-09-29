#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

bool is_woodall_number(uint64_t n) {
    if (n == 0) return false;
    for (uint64_t k = 1; (k << k) <= n; ++k) {
        uint64_t candidate = (k << k) - k;
        if (candidate == n) {
            return true;
        }
    }
    return false;
}

int main() {
    uint64_t num;
    printf("Enter a number: ");
    if (scanf("%llu", &num) != 1) {
        printf("Invalid input.\n");
        return 1;
    }
    if (is_woodall_number(num)) {
        printf("%llu is a Woodall number.\n", num);
    } else {
        printf("%llu is not a Woodall number.\n", num);
    }
    return 0;
}