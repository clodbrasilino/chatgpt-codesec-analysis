#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

int is_perfect_square(long num) {
    if (num < 0) {
        return 0;
    }
    if (num == 0) {
        return 1;
    }
    long low = 1;
    long high = num;
    while (low <= high) {
        long mid = low + (high - low) / 2;
        if (mid > 0 && mid > LONG_MAX / mid) {
            high = mid - 1;
            continue;
        }
        long square = mid * mid;
        if (square == num) {
            return 1;
        } else if (square < num) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return 0;
}

int main(int argc, char * const * argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <number>\n", argv[0]);
        return EXIT_FAILURE;
    }
    char *endptr;
    errno = 0;
    long val = strtol(argv[1], &endptr, 10);
    if (errno != 0 || *endptr != '\0' || val < 0) {
        fprintf(stderr, "Invalid input: must be a non-negative integer.\n");
        return EXIT_FAILURE;
    }
    printf("%s\n", is_perfect_square(val) ? "True" : "False");
    return EXIT_SUCCESS;
}