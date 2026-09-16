#include <stdio.h>
#include <stdlib.h>

int count_rectangles(int r) {
    if (r <= 0) {
        return 0;
    }

    int count = 0;
    long long r_sq = (long long)r * r;

    for (long long x = 1; x < r; x++) {
        long long max_y_sq = r_sq - x * x;
        
        long long low = 1;
        long long high = r - 1;
        long long y_bound = 0;

        while (low <= high) {
            long long mid = low + (high - low) / 2;
            if (mid * mid <= max_y_sq) {
                y_bound = mid;
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }
        
        count += (int)y_bound;
    }

    return count * 4;
}

int main(int argc, char * const argv[]) {
    if (argc != 2) {
        return EXIT_FAILURE;
    }

    char *endptr;
    long val = strtol(argv[1], &endptr, 10);

    if (*endptr != '\0' || val <= 0 || val > 2147483647) {
        return EXIT_FAILURE;
    }

    int r = (int)val;
    int result = count_rectangles(r);
    
    printf("%d\n", result);

    return EXIT_SUCCESS;
}