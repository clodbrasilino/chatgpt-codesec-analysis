#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int count_rectangles(int r) {
    if (r <= 1) {
        return 0;
    }

    int count = 0;
    long long r_sq = (long long)r * r;

    for (long long x = 1; x < r; x++) {
        long long max_y_sq = r_sq - x * x;
        long long y_bound = (long long)floor(sqrt((double)max_y_sq));
        
        if (y_bound * y_bound > max_y_sq) {
            y_bound--;
        }

        if (y_bound > 0) {
            if (x == y_bound) {
                count += (int)y_bound - 1;
            } else if (x < y_bound) {
                count += (int)y_bound;
            }
        }
    }

    return count * 8;
}

int main(int argc, char * const * const argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <radius>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *endptr;
    long val = strtol(argv[1], &endptr, 10);

    if (*endptr != '\0' || val <= 0 || val > 2147483647) {
        fprintf(stderr, "Invalid radius. Must be a positive integer <= 2147483647.\n");
        return EXIT_FAILURE;
    }

    int r = (int)val;
    int result = count_rectangles(r);
    
    printf("%d\n", result);

    return EXIT_SUCCESS;
}