#include <stdio.h>
#include <stdlib.h>

double sum_inverse_divisors(int n) {
    if (n <= 0) {
        return 0.0;
    }
    double sum = 0.0;
    for (int i = 1; i <= n; i++) {
        if (n % i == 0) {
            sum += 1.0 / (double)i;
        }
    }
    return sum;
}

int main(int argc, char *argv[]) {
    int n;
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <integer>\n", argv[0]);
        return 1;
    }
    char *endptr;
    long val = strtol(argv[1], &endptr, 10);
    if (*endptr != '\0' || val <= 0 || val > 2147483647) {
        fprintf(stderr, "Invalid input. Please provide a positive integer.\n");
        return 1;
    }
    n = (int)val;
    double result = sum_inverse_divisors(n);
    printf("%f\n", result);
    return 0;
}