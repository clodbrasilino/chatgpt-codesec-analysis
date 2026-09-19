#include <stdio.h>

int is_perfect_square(long long num) {
    if (num < 0) {
        return 0;
    }
    if (num == 0) {
        return 1;
    }
    long long low = 1;
    long long high = num;
    while (low <= high) {
        long long mid = low + (high - low) / 2;
        long long sq = mid * mid;
        if (sq == num) {
            return 1;
        }
        if (sq < num) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return 0;
}

int main(void) {
    long long val;
    if (scanf("%lld", &val) == 1) {
        if (is_perfect_square(val)) {
            printf("True\n");
        } else {
            printf("False\n");
        }
    }
    return 0;
}