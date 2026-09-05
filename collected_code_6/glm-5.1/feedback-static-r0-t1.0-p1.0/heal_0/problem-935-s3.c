#include <stdio.h>
#include <limits.h>

unsigned long long sum_of_squares(unsigned int n) {
    unsigned long long sum = 0;
    for (unsigned int i = 1; i <= n; ++i) {
        if (sum > ULLONG_MAX - (unsigned long long)i * i) {
            return 0;
        }
        sum += (unsigned long long)i * i;
    }
    return sum;
}

int main(void) {
    unsigned int n;
    int ret = scanf("%u", &n);
    if (ret != 1) {
        return 1;
    }
    unsigned long long result = sum_of_squares(n);
    if (result == 0 && n > 0) {
        return 1;
    }
    printf("%llu\n", result);
    return 0;
}