#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

long cube_sum_of_n(long n) {
    if (n < 1) return 0;
    long sum = 0;
    for (long i = 1; i <= n; i++) {
        sum += (i * i * i);
    }
    return sum;
}

int main() {
    long n;
    printf("Enter a positive integer: ");
    if (scanf("%ld", &n) != 1 || n < 1) {
        printf("Please enter a valid positive integer.\n");
        return 1;
    }
    long result = cube_sum_of_n(n);
    printf("Cube sum of the first %ld natural numbers is: %ld\n", n, result);
    return 0;
}