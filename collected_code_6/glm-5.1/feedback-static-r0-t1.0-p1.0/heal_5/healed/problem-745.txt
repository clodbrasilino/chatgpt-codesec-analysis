#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>

int is_divisible_by_digits(int num) {
    if (num <= 0) {
        return 0;
    }
    int temp = num;
    while (temp > 0) {
        int digit = temp % 10;
        if (digit == 0 || num % digit != 0) {
            return 0;
        }
        temp /= 10;
    }
    return 1;
}

void find_numbers(int lower, int upper) {
    if (lower > upper) {
        return;
    }
    for (int i = lower; i <= upper; i++) {
        if (is_divisible_by_digits(i)) {
            printf("%d\n", i);
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <lower> <upper>\n", argv[0]);
        return EXIT_FAILURE;
    }
    char *endptr1;
    char *endptr2;
    errno = 0;
    long lower_long = strtol(argv[1], &endptr1, 10);
    long upper_long = strtol(argv[2], &endptr2, 10);
    if (errno == ERANGE || *endptr1 != '\0' || *endptr2 != '\0' || lower_long < 0 || upper_long < 0 || lower_long > INT_MAX || upper_long > INT_MAX) {
        fprintf(stderr, "Invalid range. Inputs must be non-negative integers up to %d.\n", INT_MAX);
        return EXIT_FAILURE;
    }
    int lower = (int)lower_long;
    int upper = (int)upper_long;
    find_numbers(lower, upper);
    return EXIT_SUCCESS;
}