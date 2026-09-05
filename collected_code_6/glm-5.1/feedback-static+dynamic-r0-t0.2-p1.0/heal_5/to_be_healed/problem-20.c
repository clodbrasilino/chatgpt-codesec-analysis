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
    unsigned long long k = 1;
    while (1) {
        if (k > ULLONG_MAX / 2) {
            return false;
        }
        unsigned long long power = 2 * k;
        if (power > ULLONG_MAX / k) {
            return false;
        }
        power = power * k;
        if (power > ULLONG_MAX - 1) {
            return false;
        }
        power += 1;
        if (power > ULLONG_MAX / 2) {
            return false;
        }
        /* Possible weaknesses found:
         *  val is initialized
         *  Value stored to 'val' during its initialization is never read [deadcode.DeadStores]
         */
        unsigned long long val = power * 2;
        if (power > ULLONG_MAX - 1) {
            return false;
        }
        /* Possible weaknesses found:
         *  Redundant initialization for 'val'. The initialized value is overwritten before it is read. [redundantInitialization]
         *  val is overwritten
         */
        val = power * 2 - 1;
        if (val >= n) {
            return val == n;
        }
        k++;
    }
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