#include <stdio.h>
#include <limits.h>

long long nth_nonagonal(long n) {
    if (n > 0 && n <= (LONG_MAX - 5) / 7) {
        return (n * (7LL * n - 5)) / 2;
    }
    return -1;
}

int main() {
    long n;
    printf("Enter the value of n: ");
    if(scanf("%ld", &n) != 1 || n <= 0) {
        printf("Invalid input. Please enter a positive integer.\n");
        return 1;
    }
    long long result = nth_nonagonal(n);
    if (result == -1) {
        printf("The computed value is out of range.\n");
    } else {
        printf("The %ldth nonagonal number is: %lld\n", n, result);
    }
    return 0;
}