#include <stdio.h>
#include <stdlib.h>

int arithmetic_progression_sum(int first, int diff, int n, long long *result) {
    if (n <= 0) {
        return -1;
    }
    if (result == NULL) {
        return -1;
    }
    *result = (long long)n * (2LL * first + (long long)(n - 1) * diff) / 2;
    return 0;
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <first_term> <diff> <n>\n", argv[0]);
        return EXIT_FAILURE;
    }
    char *endptr1, *endptr2, *endptr3;
    long first = strtol(argv[1], &endptr1, 10);
    long diff = strtol(argv[2], &endptr2, 10);
    long n = strtol(argv[3], &endptr3, 10);
    if (*endptr1 != '\0' || *endptr2 != '\0' || *endptr3 != '\0') {
        fprintf(stderr, "Invalid input format\n");
        return EXIT_FAILURE;
    }
    if (n <= 0) {
        fprintf(stderr, "n must be a positive integer\n");
        return EXIT_FAILURE;
    }
    long long result;
    int ret = arithmetic_progression_sum((int)first, (int)diff, (int)n, &result);
    if (ret != 0) {
        fprintf(stderr, "Failed to calculate sum\n");
        return EXIT_FAILURE;
    }
    printf("%lld\n", result);
    return EXIT_SUCCESS;
}