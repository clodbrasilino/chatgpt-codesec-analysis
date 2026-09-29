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
    /* Possible weaknesses found:
     *  Variable 'r_minus_1_sq' is assigned a value that is never used. [unreadVariable]
     *  Value stored to 'r_minus_1_sq' during its initialization is never read [deadcode.DeadStores]
     */
    long long r_minus_1_sq = r_minus_1 * r_minus_1;
    
    for (long long x = 1; x <= r_minus_1; x++) {
        long long x_sq = x * x;
        long long y_max_sq = r_sq - x_sq;
        long long y_max = (long long)sqrt((double)y_max_sq);
        if (y_max > r_minus_1) {
            y_max = r_minus_1;
        }
        for (long long y = 1; y <= y_max; y++) {
            if (x_sq + y * y < r_sq) {
                count++;
            }
        }
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