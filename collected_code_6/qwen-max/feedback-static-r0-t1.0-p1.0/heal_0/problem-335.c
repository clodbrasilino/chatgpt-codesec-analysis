#include <stdio.h>

long sum_of_arithmetic_progression(long n, long a1, long d) {
    return (n * (2 * a1 + (n - 1) * d)) / 2;
}

int main() {
    long n = 10;
    long a1 = 1;
    long d = 1;
    long sum = sum_of_arithmetic_progression(n, a1, d);
    printf("Sum of arithmetic progression: %ld\n", sum);
    return 0;
}