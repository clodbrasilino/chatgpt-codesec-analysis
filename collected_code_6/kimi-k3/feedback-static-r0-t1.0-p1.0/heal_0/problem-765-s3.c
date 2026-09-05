#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

int is_power_of_two(unsigned long long n) {
    return n && !(n & (n - 1));
}

unsigned long long find_nth_polite(unsigned long long n) {
    unsigned long long count = 0;
    unsigned long long num = 1;

    if (n == 0) {
        return 0;
    }

    while (count < n) {
        if (!is_power_of_two(num)) {
            count++;
            if (count == n) {
                return num;
            }
        }
        if (num == ULLONG_MAX) {
            return 0;
        }
        num++;
    }
    return 0;
}

int main(void) {
    unsigned long long n;
    unsigned long long result;
    int scan_result;

    printf("Enter n: ");
    scan_result = scanf("%llu", &n);

    if (scan_result != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (n == 0) {
        fprintf(stderr, "n must be greater than 0\n");
        return EXIT_FAILURE;
    }

    result = find_nth_polite(n);

    if (result == 0) {
        fprintf(stderr, "Error: Result exceeds representable range\n");
        return EXIT_FAILURE;
    }

    printf("The %lluth polite number is: %llu\n", n, result);
    return EXIT_SUCCESS;
}