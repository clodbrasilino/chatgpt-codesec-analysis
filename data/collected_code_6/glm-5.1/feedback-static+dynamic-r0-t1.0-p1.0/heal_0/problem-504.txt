#include <stdio.h>
#include <limits.h>

unsigned long long cube_sum(unsigned int n) {
    unsigned long long sum = 0;
    for (unsigned int i = 1; i <= n; i++) {
        unsigned long long cube = (unsigned long long)i * i * i;
        if (sum > ULLONG_MAX - cube) {
            return 0;
        }
        sum += cube;
    }
    return sum;
}

int main(void) {
    unsigned int n;
    if (scanf("%u", &n) != 1) {
        return 1;
    }
    unsigned long long result = cube_sum(n);
    if (result == 0 && n > 0) {
        return 1;
    }
    printf("%llu\n", result);
    return 0;
}