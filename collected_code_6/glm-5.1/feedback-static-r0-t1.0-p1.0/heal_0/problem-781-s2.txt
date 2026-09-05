#include <stdio.h>
#include <stdlib.h>

const char* check_divisor_count_parity(long long n) {
    if (n <= 0) {
        return "invalid";
    }
    long long root = (long long)sqrt((double)n);
    if (root * root == n) {
        return "odd";
    }
    return "even";
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <positive_integer>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *endptr;
    long long val = strtoll(argv[1], &endptr, 10);

    if (*endptr != '\0' || val <= 0) {
        fprintf(stderr, "Error: Input must be a positive integer.\n");
        return EXIT_FAILURE;
    }

    const char *result = check_divisor_count_parity(val);
    printf("%s\n", result);

    return EXIT_SUCCESS;
}