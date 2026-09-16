#include <stdio.h>
#include <limits.h>

int is_woodall(unsigned long long x) {
    unsigned long long n = 1;
    unsigned long long woodall;
    unsigned long long power_of_2;

    while (n < 64) {
        power_of_2 = 1ULL << n;
        if (power_of_2 > ULLONG_MAX / n) {
            break;
        }
        woodall = n * power_of_2 - 1;
        if (woodall == x) {
            return 1;
        }
        if (woodall > x) {
            break;
        }
        n++;
    }
    return 0;
}

int main(void) {
    unsigned long long num;
    if (scanf("%llu", &num) == 1) {
        if (is_woodall(num)) {
            printf("Yes\n");
        } else {
            printf("No\n");
        }
    }
    return 0;
}