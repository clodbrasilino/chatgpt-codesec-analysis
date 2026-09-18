#include <stdio.h>
#include <stdint.h>
#include <limits.h>
#include <inttypes.h>

int64_t decagonal_number(int64_t n) {
    if (n <= 0 || n > (INT64_MAX / 4)) {
        return -1;
    }
    int64_t part1 = 4 * n * n;
    if (part1 < 0 || n > (INT64_MAX / 3)) {
        return -1;
    }
    int64_t part2 = 3 * n;
    if (part2 < 0 || part1 < part2) {
        return -1;
    }
    return part1 - part2;
}

int main() {
    int64_t n;
    printf("Enter the value of n: ");
    if (scanf("%" SCNd64, &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    int64_t result = decagonal_number(n);
    if (result == -1) {
        return 1;
    }
    printf("The %" PRId64 "th decagonal number is: %" PRId64 "\n", n, result);
    return 0;
}