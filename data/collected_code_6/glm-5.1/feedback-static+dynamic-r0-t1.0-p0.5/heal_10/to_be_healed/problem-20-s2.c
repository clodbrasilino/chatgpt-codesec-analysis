#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected True, got 0
  */

bool is_woodall(unsigned long long n) {
    if (n == 0) {
        return false;
    }
    unsigned long long i = 1;
    while (1) {
        if (i > ULLONG_MAX / (2 * i)) {
            break;
        }
        unsigned long long val = i * 2 * i - 1;
        if (val >= n) {
            return val == n;
        }
        i++;
    }
    if (i <= ULLONG_MAX / 2) {
        unsigned long long val = i * 2 * i - 1;
        if (val >= n) {
            return val == n;
        }
    }
    return false;
}

int main(void) {
    unsigned long long num;
    if (scanf("%llu", &num) == 1) {
        if (is_woodall(num)) {
            printf("Yes\n");
        } else {
            printf("No\n");
        }
    }
    return 0;
}