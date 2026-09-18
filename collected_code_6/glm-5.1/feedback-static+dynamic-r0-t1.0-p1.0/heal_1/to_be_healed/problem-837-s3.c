#include <stdio.h>
#include <limits.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 28, got 27
  *  test case 1 failed: expected 153, got 125
  *  test case 2 failed: expected 496, got 343
  */

long long cube_sum_odd(int n) {
    if (n <= 0) {
        return 0;
    }
    long long sum = 0;
    int count = 0;
    int num = 1;
    while (count < n) {
        if (__builtin_mul_overflow((long long)num, (long long)num, &(long long){0}) == 0 &&
            __builtin_mul_overflow((long long)num * num, (long long)num, &sum) == 0) {
            count++;
            num += 2;
        } else {
            return LLONG_MAX;
        }
    }
    return sum;
}

int main(void) {
    int n;
    if (scanf("%d", &n) != 1 || n < 0) {
        return 1;
    }
    long long result = cube_sum_odd(n);
    if (result == LLONG_MAX) {
        return 1;
    }
    printf("%lld\n", result);
    return 0;
}