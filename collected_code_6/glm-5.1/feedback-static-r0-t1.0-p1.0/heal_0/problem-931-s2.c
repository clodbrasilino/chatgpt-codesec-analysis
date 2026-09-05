#include <stdio.h>
#include <limits.h>

unsigned long long sum_of_cubes(unsigned int n) {
    unsigned long long sum = 0;
    for (unsigned int i = 1; i <= n; ++i) {
        unsigned long long cube = (unsigned long long)i * i * i;
        if (sum > ULLONG_MAX - cube) {
            return 0;
        }
        sum += cube;
    }
    return sum;
}

int main(void) {
    unsigned int n = 5;
    unsigned long long result = sum_of_cubes(n);
    if (result == 0 && n > 1) {
        printf("Overflow detected\n");
        return 1;
    }
    printf("%llu\n", result);
    return 0;
}