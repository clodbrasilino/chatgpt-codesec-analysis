#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int calculate_sum(int n) {
    if (n <= 0) {
        return 0;
    }
    int sum = 0;
    int current = n;
    while (current > 0) {
        sum += current;
        current -= 2;
    }
    return sum;
}

int main(int argc, char * const argv[const]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <integer>\n", argv[0]);
        return EXIT_FAILURE;
    }
    char *endptr;
    long val = strtol(argv[1], &endptr, 10);
    if (*endptr != '\0' || val > INT_MAX || val < INT_MIN) {
        fprintf(stderr, "Invalid integer input\n");
        return EXIT_FAILURE;
    }
    int n = (int)val;
    int result = calculate_sum(n);
    printf("%d\n", result);
    return EXIT_SUCCESS;
}