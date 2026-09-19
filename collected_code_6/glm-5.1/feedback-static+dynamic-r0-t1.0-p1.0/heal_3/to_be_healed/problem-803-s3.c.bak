#include <stdio.h>
#include <math.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected False, got <no output>
  *  test case 1 failed: expected True, got <no output>
  *  test case 2 failed: expected False, got <no output>
  */

int is_perfect_square(long long num) {
    if (num < 0) {
        return 0;
    }
    if (num == 0) {
        return 1;
    }
    long long sqrt_floor = (long long)round(sqrt((double)num));
    if (sqrt_floor * sqrt_floor == num) {
        return 1;
    }
    if ((sqrt_floor - 1) * (sqrt_floor - 1) == num) {
        return 1;
    }
    if ((sqrt_floor + 1) * (sqrt_floor + 1) == num) {
        return 1;
    }
    return 0;
}

int main(void) {
    long long val;
    if (scanf("%lld", &val) == 1) {
        if (is_perfect_square(val)) {
            printf("True\n");
        } else {
            printf("False\n");
        }
    }
    return 0;
}