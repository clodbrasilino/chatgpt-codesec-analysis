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

int main(int argc, char * const argv[const]) {
    int n;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <n>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (sscanf(argv[1], "%d", &n) != 1) {
        fprintf(stderr, "Invalid input: not an integer.\n");
        return EXIT_FAILURE;
    }

    if (n <= 0) {
        fprintf(stderr, "Invalid input: n must be a positive integer.\n");
        return EXIT_FAILURE;
    }

    unsigned long long result = sum_fifth_power_even(n);
    printf("%llu\n", result);

    return EXIT_SUCCESS;
}