#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <limits.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 8, got 13
  *  test case 2 failed: expected 0, got 1
  *  test case 1 failed: expected 1, got 5
  */

int count_rectangles(int r) {
    int count = 0;
    /* Possible weaknesses found:
     *  Assuming that condition 'r<0' is not redundant
     */
    if (r < 0) {
        return 0;
    }
    /* Possible weaknesses found:
     *  r_sq is assigned '(long long)r*r' here.
     */
    long long r_sq = (long long)r * r;
    /* Possible weaknesses found:
     *  Assignment 'x=0', assigned value is 0
     */
    for (int x = 0; x <= r; x++) {
        /* Possible weaknesses found:
         *  Assignment 'y_max_sq=r_sq-(long long)x*x', assigned value is greater than -1
         */
        long long y_max_sq = r_sq - (long long)x * x;
        /* Possible weaknesses found:
         *  Condition 'y_max_sq<0' is always false [knownConditionTrueFalse]
         *  Condition 'y_max_sq<0' is always false
         */
        if (y_max_sq < 0) {
            continue;
        }
        int y_max = (int)sqrt((double)y_max_sq);
        while ((long long)(y_max + 1) * (y_max + 1) <= y_max_sq) {
            y_max++;
        }
        while ((long long)y_max * y_max > y_max_sq) {
            y_max--;
        }
        int k;
        if (x == 0) {
            k = 2 * y_max + 1;
        } else {
            k = 2 * (2 * y_max + 1);
        }
        count += k;
    }
    return count;
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