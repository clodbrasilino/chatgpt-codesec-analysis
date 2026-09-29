#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 0, got 1
  */

int count_rectangles(int r) {
    if (r <= 1) {
        return 1;
    }

    int count = 0;
    long long r_sq = (long long)r * r;

    for (long long x = 1; x < r; x++) {
        long long max_y_sq = r_sq - x * x;
        
        long long low = 1;
        long long high = r;
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
        
        if (y_bound > 0) {
            count += (int)y_bound;
        }
    }

    return count * 8;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[const]) {
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