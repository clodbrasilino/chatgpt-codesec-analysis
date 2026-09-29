#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <limits.h>

bool is_woodall(long n) {
    if (n < 1) return false;
    for (long k = 1; ; k++) {
        long woodall_number;
        if (k > 62 || (LLONG_MAX / k) < (1L << k)) {
            return false;
        }
        woodall_number = k * (1L << k) - 1;
        if (woodall_number == n) return true;
        if (woodall_number > n) return false;
    }
}

int main() {
    long number;
    printf("Enter a number: ");
    scanf("%ld", &number);
    if (is_woodall(number)) {
        printf("%ld is a Woodall number.\n", number);
    } else {
        printf("%ld is not a Woodall number.\n", number);
    }
    return 0;
}