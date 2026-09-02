#include <stdio.h>

long sum_of_squares(long n) {
    return (n * (n + 1) * (2 * n + 1)) / 6;
}

int main() {
    long n = 5;
    printf("Sum of squares up to %ld: %ld\n", n, sum_of_squares(n));
    return 0;
}