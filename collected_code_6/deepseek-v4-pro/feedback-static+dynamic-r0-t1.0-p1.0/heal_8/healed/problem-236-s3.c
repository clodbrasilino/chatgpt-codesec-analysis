#include <stdio.h>
#include <stdlib.h>

static long long count_equilateral_triangles(int n) {
    long long count = 0;
    for (int i = 1; i <= n; i++) {
        count += (long long)i * (n - i + 1);
    }
    for (int i = 1; i <= n / 2; i++) {
        count += (long long)i * (n - 2 * i + 1);
    }
    return count;
}

int main(int argc, char *const argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <side_length>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *endptr;
    long val = strtol(argv[1], &endptr, 10);

    if (endptr == argv[1] || *endptr != '\0') {
        fprintf(stderr, "Error: Invalid input, must be an integer\n");
        return EXIT_FAILURE;
    }

    if (val <= 0 || val > 1000000) {
        fprintf(stderr, "Error: side_length must be between 1 and 1000000\n");
        return EXIT_FAILURE;
    }

    int n = (int)val;
    long long result = count_equilateral_triangles(n);
    printf("%lld\n", result);

    return EXIT_SUCCESS;
}