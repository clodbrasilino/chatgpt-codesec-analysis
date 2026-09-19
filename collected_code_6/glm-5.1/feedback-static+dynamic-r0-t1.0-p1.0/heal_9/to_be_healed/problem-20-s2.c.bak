#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected True, got 0
  */

bool is_woodall(unsigned long long n) {
    if (n == 0) {
        return false;
    }

    for (unsigned long long i = 1; i < 64; i++) {
        if (i > n) {
            break;
        }
        unsigned long long term = (1ULL << i) - 1;
        if (term > n / i) {
            break;
        }
        if (i * term == n) {
            return true;
        }
    }

    return false;
}

int main(void) {
    unsigned long long num;

    if (scanf("%llu", &num) != 1) {
        return 1;
    }

    if (is_woodall(num)) {
        printf("True\n");
    } else {
        printf("False\n");
    }

    return 0;
}