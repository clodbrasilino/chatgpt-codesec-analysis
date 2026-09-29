#include <stdio.h>
#include <stdlib.h>

double sum_inverse_divisors(int n) {
    if (n <= 0) {
        return 0.0;
    }
    double sum = 0.0;
    for (int i = 1; i * i <= n; i++) {
        if (n % i == 0) {
            sum += 1.0 / i;
            if (i != n / i) {
                sum += 1.0 / (n / i);
            }
        }
    }
    return sum;
}

int main(int argc, char * const argv[]) {
    int n;
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <integer>\n", argv[0]);
        return 1;
    }
    char *endptr;
    long val = strtol(argv[1], &endptr, 10);
    if (*endptr != '\0' || val < 1 || val > 2147483647) {
        fprintf(stderr, "Error: Invalid input. Must be a positive integer.\n");
        return 1;
    }
    n = (int)val;
    double result = sum_inverse_divisors(n);
    printf("%.6f\n", result);
    return 0;
}