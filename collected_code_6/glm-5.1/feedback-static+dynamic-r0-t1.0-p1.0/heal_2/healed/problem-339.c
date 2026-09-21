#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int find_max_occurring_divisor(long l, long r) {
    long max_div = l;
    long max_count = 0;
    long *count = (long *)malloc(sizeof(long) * (r + 1));
    if (count == NULL) {
        return -1;
    }
    memset(count, 0, sizeof(long) * (r + 1));
    for (long i = l; i <= r; i++) {
        if (i == 1) {
            count[1] += 1;
        } else {
            for (long j = 1; j * j <= i; j++) {
                if (i % j == 0) {
                    count[j] += 1;
                    if (j != i / j) {
                        count[i / j] += 1;
                    }
                }
            }
        }
    }
    for (long d = 1; d <= r; d++) {
        if (count[d] > max_count) {
            max_count = count[d];
            max_div = d;
        }
    }
    free(count);
    return (int)max_div;
}

int main(int argc, char * const * const argv) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <lower_bound> <upper_bound>\n", argv[0]);
        return 1;
    }
    char *endptr1;
    char *endptr2;
    long l = strtol(argv[1], &endptr1, 10);
    long r = strtol(argv[2], &endptr2, 10);
    if (*endptr1 != '\0' || *endptr2 != '\0' || l <= 0 || r <= 0 || l > r) {
        fprintf(stderr, "Error: Bounds must be positive integers with lower <= upper.\n");
        return 1;
    }
    int result = find_max_occurring_divisor(l, r);
    if (result < 0) {
        fprintf(stderr, "Error: Memory allocation failed.\n");
        return 1;
    }
    printf("%d\n", result);
    return 0;
}