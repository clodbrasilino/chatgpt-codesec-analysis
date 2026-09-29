#include <stdio.h>
#include <stdlib.h>

long long find_difference(int n) {
    if (n <= 0) {
        exit(EXIT_FAILURE);
    }
    long long sum = (long long)n * (n + 1) / 2;
    long long sum_cubes = sum * sum;
    return sum_cubes - sum;
}

int main(void) {
    int n = 0;
    if (scanf("%d", &n) != 1) {
        exit(EXIT_FAILURE);
    }
    long long result = find_difference(n);
    printf("%lld\n", result);
    return 0;
}