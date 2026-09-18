#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

long long sum_of_fourth_powers(long n) {
    if (n < 0 || n > LLONG_MAX / 4) {
        return -1;
    }
    long long sum = 0;
    for (long i = 1; i <= n; ++i) {
        long long temp = i * i * i * i;
        if (LLONG_MAX - sum < temp) {
            return -1;
        }
        sum += temp;
    }
    return sum;
}

int main() {
    long n;
    printf("Enter a positive integer: ");
    if (scanf("%ld", &n) != 1 || n < 1) {
        fprintf(stderr, "Invalid input. Please enter a positive integer.\n");
        return 1;
    }
    long long result = sum_of_fourth_powers(n);
    if (result == -1) {
        fprintf(stderr, "Overflow detected.\n");
        return 1;
    }
    printf("The sum of the fourth powers of the first %ld natural numbers is: %lld\n", n, result);
    return 0;
}