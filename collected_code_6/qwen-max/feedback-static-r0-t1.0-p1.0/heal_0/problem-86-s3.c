#include <stdio.h>

long nth_centered_hexagonal_number(long n) {
    return 3 * n * (n - 1) + 1;
}

int main() {
    long n;
    printf("Enter the value of n: ");
    scanf("%ld", &n);
    if (n <= 0) {
        printf("Please enter a positive integer.\n");
        return 1;
    }
    long result = nth_centered_hexagonal_number(n);
    printf("The %ldth centered hexagonal number is: %ld\n", n, result);
    return 0;
}