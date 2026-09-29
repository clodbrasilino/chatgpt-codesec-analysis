#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>

long nth_tetrahedral_number(long n) {
    if (n <= 0) return 0;
    long max_div_6 = LONG_MAX / 6;
    if (n > (long)((sqrt(8.0 * (double)max_div_6 + 1.0) - 1.0) / 2.0)) {
        fprintf(stderr, "Input too large, would cause overflow.\n");
        exit(EXIT_FAILURE);
    }
    long n1 = n + 1;
    long n2 = n + 2;
    if (n < 0 || n1 < 0 || n2 < 0 || n1 >= n2 || (n1 / 6) >= (LONG_MAX / n2) || (n * (n1 / 6)) >= (LONG_MAX / n2)) {
        fprintf(stderr, "Calculation would cause overflow.\n");
        exit(EXIT_FAILURE);
    }
    return (n * (n1 * n2)) / 6;
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