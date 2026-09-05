#include <stdio.h>
#include <limits.h>

unsigned long long sum_of_cubes(unsigned long long n) {
    unsigned long long sum = 0;
    for (unsigned long long i = 1; i <= n; ++i) {
        unsigned long long cube = i * i * i;
        if (sum > ULLONG_MAX - cube) {
            return 0;
        }
        sum += cube;
    }
    return sum;
}

int main(void) {
    unsigned long long n;
    if (scanf("%llu", &n) != 1) {
        return 1;
    }
    unsigned long long result = sum_of_cubes(n);
    if (result == 0 && n > 1) {
        printf("Overflow detected\n");
        return 1;
    }
    printf("%llu\n", result);
    return 0;
}