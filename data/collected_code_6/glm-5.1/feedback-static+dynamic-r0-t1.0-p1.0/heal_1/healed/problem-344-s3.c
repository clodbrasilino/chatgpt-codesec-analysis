#include <stdio.h>
#include <stdlib.h>

int count_odd_factors(int start, int end) {
    if (start > end) {
        return 0;
    }

    int count = 0;

    for (int i = start; i <= end; i++) {
        if (i <= 0) {
            continue;
        }
        int sqrt_i = 1;
        while (sqrt_i * sqrt_i <= i) {
            sqrt_i++;
        }
        sqrt_i--;

        if (sqrt_i * sqrt_i != i) {
            count++;
        }
    }

    return count;
}

int main(int argc, char * const argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <start> <end>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *endptr_start = NULL;
    char *endptr_end = NULL;
    long val_start = strtol(argv[1], &endptr_start, 10);
    long val_end = strtol(argv[2], &endptr_end, 10);

    if (endptr_start == argv[1] || *endptr_start != '\0' || val_start < 0 || val_start > 2147483647) {
        fprintf(stderr, "Invalid start value\n");
        return EXIT_FAILURE;
    }

    if (endptr_end == argv[2] || *endptr_end != '\0' || val_end < 0 || val_end > 2147483647) {
        fprintf(stderr, "Invalid end value\n");
        return EXIT_FAILURE;
    }

    int start = (int)val_start;
    int end = (int)val_end;

    int result = count_odd_factors(start, end);
    printf("%d\n", result);

    return EXIT_SUCCESS;
}