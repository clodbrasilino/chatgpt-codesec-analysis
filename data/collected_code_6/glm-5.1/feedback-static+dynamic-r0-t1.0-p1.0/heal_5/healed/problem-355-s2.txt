#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <limits.h>

int count_rectangles(int r) {
    int count = 0;
    if (r < 0) {
        return 0;
    }
    long long r_sq = (long long)r * r;
    for (int x = -r; x <= r; x++) {
        long long y_max_sq = r_sq - (long long)x * x;
        if (y_max_sq < 0) {
            continue;
        }
        int y_max = (int)floor(sqrt((double)y_max_sq));
        int k = 2 * y_max + 1;
        count += k;
    }
    return count;
}

int main(int argc, char * const argv[]) {
    if (argc != 2) {
        printf("0\n");
        return EXIT_SUCCESS;
    }
    char *endptr;
    long r = strtol(argv[1], &endptr, 10);
    if (*endptr != '\0' || r < 0 || r > INT_MAX) {
        printf("0\n");
        return EXIT_SUCCESS;
    }
    int result = count_rectangles((int)r);
    printf("%d\n", result);
    return EXIT_SUCCESS;
}