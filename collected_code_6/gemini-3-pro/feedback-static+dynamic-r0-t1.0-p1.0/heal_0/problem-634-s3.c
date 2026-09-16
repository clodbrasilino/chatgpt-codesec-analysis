#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

unsigned long long sum_of_fourth_power_of_even_numbers(int n) {
    if (n < 0) {
        return 0;
    }

    unsigned long long sum = 0;
    for (int i = 1; i <= n; i++) {
        unsigned long long even_num = 2ULL * i;
        sum += even_num * even_num * even_num * even_num;
    }

    return sum;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <n>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *endptr;
    errno = 0;
    long val = strtol(argv[1], &endptr, 10);

    if (errno != 0 || *endptr != '\0' || val < 0) {
        fprintf(stderr, "Invalid input. Please provide a non-negative integer.\n");
        return EXIT_FAILURE;
    }

    int n = (int)val;
    unsigned long long result = sum_of_fourth_power_of_even_numbers(n);

    printf("%llu\n", result);

    return EXIT_SUCCESS;
}