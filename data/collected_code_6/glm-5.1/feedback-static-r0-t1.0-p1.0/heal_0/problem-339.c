#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int find_max_occurring_divisor(int l, int r) {
    int max_div = l;
    int max_count = 0;
    int *count = (int *)malloc(sizeof(int) * (r + 1));
    if (count == NULL) {
        return -1;
    }
    memset(count, 0, sizeof(int) * (r + 1));
    for (int i = l; i <= r; i++) {
        if (i == 1) {
            count[1] += 1;
        } else {
            for (int j = 1; j * j <= i; j++) {
                if (i % j == 0) {
                    count[j] += 1;
                    if (j != i / j) {
                        count[i / j] += 1;
                    }
                }
            }
        }
    }
    for (int d = 1; d <= r; d++) {
        if (count[d] > max_count) {
            max_count = count[d];
            max_div = d;
        }
    }
    free(count);
    return max_div;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <lower_bound> <upper_bound>\n", argv[0]);
        return 1;
    }
    int l = atoi(argv[1]);
    int r = atoi(argv[2]);
    if (l <= 0 || r <= 0 || l > r) {
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