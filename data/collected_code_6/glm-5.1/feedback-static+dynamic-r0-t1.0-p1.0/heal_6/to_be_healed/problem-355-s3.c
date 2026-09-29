#include <stdio.h>
#include <stdlib.h>
#include <math.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 8, got 4
  *  test case 1 failed: expected 1, got 0
  */

long long count_rectangles(int r) {
    if (r < 1) {
        return 0;
    }

    long long count = 0;
    long long r_sq = (long long)r * r;
    long long r_minus_1 = (long long)r - 1;
    
    for (long long x = 1; x <= r_minus_1; x++) {
        long long x_sq = x * x;
        long long y_max_sq = r_sq - x_sq;
        long long y_max = (long long)sqrt((double)y_max_sq);
        
        while (y_max * y_max >= y_max_sq) {
            y_max--;
        }
        while ((y_max + 1) * (y_max + 1) < y_max_sq) {
            y_max++;
        }

        if (y_max > r_minus_1) {
            y_max = r_minus_1;
        }
        
        count += y_max;
    }

    return count * 4;
}

int main(int argc, char const * const argv[]) {
    if (argc != 2) {
        return EXIT_FAILURE;
    }

    char *endptr;
    long val = strtol(argv[1], &endptr, 10);

    if (endptr == argv[1] || *endptr != '\0' || val < 0 || val > 10000) {
        return EXIT_FAILURE;
    }

    long long result = count_rectangles((int)val);
    printf("%lld\n", result);

    return EXIT_SUCCESS;
}