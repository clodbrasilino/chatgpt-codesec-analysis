#include <stdio.h>
#include <stdlib.h>

unsigned long long perrin(int n) {
    if (n < 0) {
        return 0;
    }
    if (n == 0) {
        return 3;
    }
    if (n == 1) {
        return 0;
    }
    if (n == 2) {
        return 2;
    }
    return perrin(n - 2) + perrin(n - 3);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <n>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *endptr;
    long n_long = strtol(argv[1], &endptr, 10);

    if (*endptr != '\0' || n_long < 0 || n_long > 100) {
        fprintf(stderr, "Error: Invalid input. Please provide a non-negative integer (<= 100).\n");
        return EXIT_FAILURE;
    }

    int n = (int)n_long;
    unsigned long long result = perrin(n);

    printf("%llu\n", result);

    return EXIT_SUCCESS;
}