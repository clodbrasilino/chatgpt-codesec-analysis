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
    while (k < 64) {
        unsigned long long power = 1ULL << k;
        if (k > ULLONG_MAX / (power - 1)) {
            break;
        }
        unsigned long long term = k * (power - 1);
        if (term == n) {
            return true;
        }
        if (term > n) {
            break;
        }
        k++;
    }
    return false;
}

int main(void) {
    unsigned long long num;
    if (scanf("%llu", &num) != 1) {
        return 1;
    }
    printf("%d\n", is_woodall(num) ? 1 : 0);
    return 0;
}