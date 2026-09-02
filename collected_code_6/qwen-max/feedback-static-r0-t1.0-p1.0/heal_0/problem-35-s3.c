#include <stdio.h>

long nth_rectangular_number(long n) {
    return n * (n + 1);
}

int main() {
    long n;
    printf("Enter the value of n: ");
    if (scanf("%ld", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    if (n < 1) {
        fprintf(stderr, "n must be a positive integer\n");
        return 1;
    }
    printf("The %ld-th rectangular number is: %ld\n", n, nth_rectangular_number(n));
    return 0;
}