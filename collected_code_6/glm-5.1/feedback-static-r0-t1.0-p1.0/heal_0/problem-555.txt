#include <stdio.h>

unsigned long long find_difference(unsigned int n) {
    if (n == 0) {
        return 0;
    }

    unsigned long long sum = (unsigned long long)n * (n + 1) / 2;
    unsigned long long sum_cubes = sum * sum;

    return sum_cubes - sum;
}

int main(void) {
    unsigned int n;
    
    if (scanf("%u", &n) != 1) {
        return 1;
    }

    unsigned long long result = find_difference(n);
    
    if (printf("%llu\n", result) < 0) {
        return 1;
    }

    return 0;
}