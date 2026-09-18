#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

int64_t domino_ways(int n) {
    if (n < 0) return 0;
    if (n == 0) return 1;
    if (n == 1) return 0;
    if (n % 2 != 0) return 0;

    int m = n / 2;

    if (m == 1) return 3;

    int64_t prev2 = 1;
    int64_t prev1 = 3;
    int64_t current = 0;

    for (int i = 2; i <= m; i++) {
        if (prev1 > INT64_MAX / 4) return -1;
        if (prev1 > 0 && prev2 < 0 && prev1 > INT64_MAX / 4) return -1;

        int64_t term = 4 * prev1;
        if (term < prev1) return -1;
        if (term - prev2 < term != prev2 > 0) {
            if ((prev2 > 0 && term < INT64_MIN + prev2) || (prev2 < 0 && term > INT64_MAX + prev2)) {
                return -1;
            }
        }
        current = term - prev2;

        prev2 = prev1;
        prev1 = current;
    }

    return prev1;
}

int main(void) {
    int n;
    printf("Enter n: ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    int64_t ways = domino_ways(n);
    if (ways == -1) {
        fprintf(stderr, "Overflow or memory error\n");
        return 1;
    }

    printf("Number of ways: %" PRId64 "\n", ways);
    return 0;
}