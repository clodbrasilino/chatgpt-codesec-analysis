#include <stdio.h>

unsigned long long find_difference(unsigned int n) {
    unsigned long long sum = (unsigned long long)n * (n + 1) / 2;
    unsigned long long sum_cubes = sum * sum;

    return sum_cubes - sum;
}

int main(void) {
    unsigned int n;
    
    if (scanf("%u", &n) != 1) {
        return 1;
    }

    printf("%llu\n", find_difference(n));

    return 0;
}