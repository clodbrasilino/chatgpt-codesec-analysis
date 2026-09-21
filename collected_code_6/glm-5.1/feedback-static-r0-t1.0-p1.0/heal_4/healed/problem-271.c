#include <stdio.h>
#include <stdlib.h>
#include <math.h>

unsigned long long sum_fifth_power_even(int n) {
    if (n <= 0) {
        return 0;
    }

    unsigned long long sum = 0;
    for (int i = 1; i <= n; i++) {
        unsigned long long even_num = 2ULL * i;
        unsigned long long term = even_num * even_num * even_num * even_num * even_num;
        sum += term;
    }

    return sum;
}

int main(int argc, char * const *argv) {
    int n;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <n>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *endptr;
    long val = strtol(argv[1], &endptr, 10);
    if (*endptr != '\0' || val <= 0 || val > 2147483647) {
        fprintf(stderr, "Invalid input: n must be a positive integer.\n");
        return EXIT_FAILURE;
    }
    n = (int)val;

    unsigned long long result = sum_fifth_power_even(n);
    printf("%llu\n", result);

    return EXIT_SUCCESS;
}