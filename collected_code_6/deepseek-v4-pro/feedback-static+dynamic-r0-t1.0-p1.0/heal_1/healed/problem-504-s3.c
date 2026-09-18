#include <stdio.h>
#include <limits.h>

long long cube_sum(int n) {
    long long sum = 0;
    for (int i = 1; i <= n; ++i) {
        if (i > 2097151) {
            return -1;
        }
        long long cube = (long long)i * i * i;
        if (sum > LLONG_MAX - cube) {
            return -1;
        }
        sum += cube;
    }
    return sum;
}

int main(void) {
    int n;
    printf("Enter a natural number: ");
    if (scanf("%d", &n) != 1 || n < 1) {
        fprintf(stderr, "Invalid input. Please enter a positive integer.\n");
        return 1;
    }
    long long result = cube_sum(n);
    if (result == -1) {
        fprintf(stderr, "Input too large, overflow would occur.\n");
        return 1;
    }
    printf("Cube sum = %lld\n", result);
    return 0;
}