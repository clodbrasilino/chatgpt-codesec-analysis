#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

bool is_within_limit(long n) {
    return n > 0 && n <= LONG_MAX / 4;
}

long nth_hexagonal_number(long n) {
    if (is_within_limit(n)) {
        return 2 * n * (2 * n - 1);
    } else {
        return -1;
    }
}

int main() {
    long n;
    printf("Enter the value of n: ");
    if (scanf("%ld", &n) == 1) {
        long hex_num = nth_hexagonal_number(n);
        if (hex_num != -1) {
            printf("The %ldth hexagonal number is %ld\n", n, hex_num);
        } else {
            printf("Input too large for calculation.\n");
        }
    } else {
        printf("Invalid input.\n");
    }
    return 0;
}