#include <stdio.h>
#include <stdlib.h>

int is_perfect_square(int num) {
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

int main(int argc, char const * const argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <number>\n", argv[0]);
        return EXIT_FAILURE;
    }
    char *endptr;
    long val = strtol(argv[1], &endptr, 10);
    if (*endptr != '\0' || val < 0 || val > 2147483647) {
        fprintf(stderr, "Invalid input: must be a non-negative integer.\n");
        return EXIT_FAILURE;
    }
    int num = (int)val;
    if (is_perfect_square(num)) {
        printf("%d is a perfect square.\n", num);
    } else {
        printf("%d is not a perfect square.\n", num);
    }
    return EXIT_SUCCESS;
}