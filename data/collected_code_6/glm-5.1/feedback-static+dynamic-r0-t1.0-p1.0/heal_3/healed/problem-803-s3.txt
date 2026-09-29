#include <stdio.h>
#include <math.h>

int is_perfect_square(long long num) {
    if (num < 0) {
        return 0;
    }
    if (num == 0) {
        return 1;
    }
    long long sqrt_floor = (long long)sqrt((double)num);
    while (sqrt_floor > 0 && sqrt_floor * sqrt_floor > num) {
        sqrt_floor--;
    }
    while (sqrt_floor <= 3037000499LL && (sqrt_floor + 1) * (sqrt_floor + 1) <= num) {
        sqrt_floor++;
    }
    return (sqrt_floor * sqrt_floor == num);
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