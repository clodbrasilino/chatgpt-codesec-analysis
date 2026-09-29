#include <stdio.h>
#include <stdlib.h>

long nth_tetrahedral_number(long n) {
    if (n <= 0) return 0;
    return n * (n + 1) * (n + 2) / 6;
}

int main() {
    long n;
    printf("Enter the value of n: ");
    if (scanf("%ld", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        exit(EXIT_FAILURE);
    }
    long result = nth_tetrahedral_number(n);
    printf("The %ldth tetrahedral number is: %ld\n", n, result);
    return 0;
}