#include <stdio.h>
#include <stdlib.h>

int sum_divisors(int n) {
    if (n <= 1) {
        return 0;
    }
    int sum = 1;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            sum += i;
            int complement = n / i;
            if (complement != i) {
                sum += complement;
            }
        }
    }
    return sum;
}

long long sum_amicable_numbers(int limit) {
    if (limit <= 1) {
        return 0;
    }
    long long total = 0;
    int *proper_sums = (int *)malloc((limit + 1) * sizeof(int));
    if (proper_sums == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 2; i <= limit; i++) {
        proper_sums[i] = sum_divisors(i);
    }
    for (int a = 2; a <= limit; a++) {
        int b = proper_sums[a];
        if (b > a && b <= limit) {
            if (proper_sums[b] == a) {
                total += a + b;
            }
        }
    }
    free(proper_sums);
    return total;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <limit>\n", argv[0]);
        return EXIT_FAILURE;
    }
    char *endptr;
    long val = strtol(argv[1], &endptr, 10);
    if (endptr == argv[1] || *endptr != '\0' || val <= 0 || val > 1000000) {
        fprintf(stderr, "Invalid limit. Please provide an integer between 1 and 1000000.\n");
        return EXIT_FAILURE;
    }
    int limit = (int)val;
    long long result = sum_amicable_numbers(limit);
    printf("%lld\n", result);
    return EXIT_SUCCESS;
}