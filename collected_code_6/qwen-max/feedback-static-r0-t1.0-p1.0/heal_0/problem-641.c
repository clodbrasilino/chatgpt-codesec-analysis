#include <stdio.h>

long long nth_nonagonal_number(long n) {
    return (7 * n * n - 5 * n) / 2;
}

int main() {
    long n;
    printf("Enter the value of n: ");
    if (scanf("%ld", &n) == 1) {
        if (n > 0) {
            long long result = nth_nonagonal_number(n);
            printf("The %ldth nonagonal number is: %lld\n", n, result);
        } else {
            printf("Please enter a positive integer.\n");
        }
    } else {
        printf("Invalid input. Please enter an integer.\n");
    }
    return 0;
}