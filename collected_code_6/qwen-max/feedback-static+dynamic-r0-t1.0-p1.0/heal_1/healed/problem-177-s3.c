#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <limits.h>

int64_t gcd(int64_t a, int64_t b) {
    while (b != 0) {
        int64_t t = b;
        b = a % b;
        a = t;
    }
    return a;
}

int64_t lcm(int64_t a, int64_t b) {
    if (a == 0 || b == 0) return 0;
    return (a / gcd(a, b)) * b;
}

int find_numbers_in_range(int64_t lower, int64_t upper) {
    for (int64_t i = lower; i <= upper; i++) {
        for (int64_t j = i + 1; j <= upper; j++) {
            int64_t result = lcm(i, j);
            if (result >= lower && result <= upper) {
                printf("Found numbers: %lld and %lld\n", i, j);
                return 0;
            }
        }
    }
    return -1;
}

int main() {
    int64_t lower, upper;

    printf("Enter the lower and upper bounds of the range: ");
    if (scanf("%lld %lld", &lower, &upper) != 2) {
        printf("Invalid input.\n");
        return 1;
    }

    if (find_numbers_in_range(lower, upper) == -1) {
        printf("No such numbers found in the given range.\n");
    }

    return 0;
}