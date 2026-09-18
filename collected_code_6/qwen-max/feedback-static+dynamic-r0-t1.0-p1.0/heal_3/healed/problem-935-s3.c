#include <stdio.h>
#include <stdint.h>
#include <limits.h>

long long sum_of_squares(int n) {
    if (n > 0 && n <= INT_MAX / 2) {
        int64_t n_squared = (int64_t)n * n;
        int64_t two_n_plus_one = 2 * n + 1;
        if (two_n_plus_one > 0 && n_squared <= LLONG_MAX / two_n_plus_one / 6) {
            int64_t n_times_n_plus_one = (int64_t)n * (n + 1);
            return (n_times_n_plus_one * two_n_plus_one) / 6;
        }
    }
    return -1;
}

int main() {
    int n;
    printf("Enter a positive integer: ");
    if (scanf("%d", &n) != 1 || n < 1) {
        fprintf(stderr, "Invalid input. Please enter a positive integer.\n");
        return 1;
    }
    long long result = sum_of_squares(n);
    if (result == -1) {
        fprintf(stderr, "Overflow detected. The number is too large.\n");
        return 1;
    }
    printf("The sum of squares from 1 to %d is: %lld\n", n, result);
    return 0;
}