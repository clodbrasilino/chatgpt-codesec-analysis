#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <limits.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 0, got 1
  *  test case 0 failed: expected 8, got 17
  *  test case 1 failed: expected 1, got 5
  */

int count_rectangles(int r) {
    int count = 0;
    if (r < 0) {
        return 0;
    }
    if (r == 0) {
        return 1;
    }
    long long r_sq = (long long)r * r;
    for (int x = -r; x <= r; x++) {
        for (int y = -r; y <= r; y++) {
            if ((long long)x * x + (long long)y * y <= r_sq) {
                if (x != 0 || y != 0) {
                    if ((x > 0 && y >= 0) || (x < 0 && y < 0)) {
                        count++;
                    }
                }
            }
        }
    }
    return count * 4 + 1;
}

int main(int argc, char const * const argv[]) {
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