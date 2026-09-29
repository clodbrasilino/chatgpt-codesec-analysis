#include <stdio.h>
#include <limits.h>
#include <inttypes.h>

long long nth_nonagonal_number(long n) {
    if (n > 0 && n <= (LONG_MAX - 5) / 14) {
        long long nn = (long long)n;
        long long result1 = 7 * nn * nn;
        long long result2 = 5 * nn;
        if (result1 < 0 || result2 < 0 || (result1 - result2) < 0 || (result1 - result2) % 2 != 0) {
            return -1;
        }
        long long result = (result1 - result2) / 2;
        if (result > LLONG_MAX) {
            return -1;
        }
        return result;
    } else {
        return -1;
    }
}

int main() {
    long n;
    printf("Enter the value of n: ");
    if (scanf("%ld", &n) == 1) {
        if (n > 0) {
            long long result = nth_nonagonal_number(n);
            if (result != -1) {
                printf("The %ldth nonagonal number is: %lld\n", n, result);
            } else {
                printf("Input too large for safe computation.\n");
            }
        } else {
            printf("Please enter a positive integer.\n");
        }
    } else {
        printf("Invalid input. Please enter an integer.\n");
    }
    return 0;
}