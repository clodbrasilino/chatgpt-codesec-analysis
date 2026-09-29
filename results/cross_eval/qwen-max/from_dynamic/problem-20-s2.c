#include <stdio.h>
#include <math.h>
#include <limits.h>

int is_woodall(long n) {
    for (long k = 1; ; ++k) {
        long max_power = (LONG_MAX - 1) / k;
        double power = pow(2, k);
        if (power > max_power) break;
        long woodall_number = k * (long)power - 1;
        if (woodall_number == n) return 1;
        if (woodall_number > n) break;
    }
    return 0;
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