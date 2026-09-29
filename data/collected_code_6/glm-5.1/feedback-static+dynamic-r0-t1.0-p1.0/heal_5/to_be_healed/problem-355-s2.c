#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <limits.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 8, got 9
  *  test case 2 failed: expected 0, got 1
  *  test case 1 failed: expected 1, got 3
  */

int count_rectangles(int r) {
    int count = 0;
    if (r < 0) {
        return 0;
    }
    long long r_sq = (long long)r * r;
    for (int x = -r + 1; x < r; x++) {
        long long y_max_sq = r_sq - (long long)x * x;
        if (y_max_sq < 0) {
            continue;
        }
        int y_max = (int)floor(sqrt((double)y_max_sq));
        int k = 2 * y_max;
        count += k;
    }
    return count + 1;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
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