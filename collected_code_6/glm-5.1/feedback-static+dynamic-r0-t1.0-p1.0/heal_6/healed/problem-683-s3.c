#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <limits.h>
#include <string.h>

bool canBeSumOfTwoSquares(int n) {
    if (n < 0) {
        return false;
    }
    long long limit = (long long)sqrt((double)n);
    for (long long a = 0; a <= limit; a++) {
        long long b_squared = (long long)n - a * a;
        if (b_squared < 0) {
            break;
        }
        long long b = (long long)sqrt((double)b_squared);
        if (b * b == b_squared) {
            return true;
        }
    }
    return false;
}

int main(int argc, char * argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <number>\n", argv[0]);
        return EXIT_FAILURE;
    }
    size_t len = strnlen(argv[1], 32);
    if (len >= 32) {
        fprintf(stderr, "Invalid input: Input length exceeded\n");
        return EXIT_FAILURE;
    }
    char num_str[32];
    memcpy(num_str, argv[1], len);
    num_str[len] = '\0';
    char *endptr;
    long val = strtol(num_str, &endptr, 10);
    if (endptr == num_str || *endptr != '\0' || val < INT_MIN || val > INT_MAX) {
        fprintf(stderr, "Invalid input: Not a valid integer\n");
        return EXIT_FAILURE;
    }
    if (canBeSumOfTwoSquares((int)val)) {
        printf("Yes\n");
    } else {
        printf("No\n");
    }
    return EXIT_SUCCESS;
}