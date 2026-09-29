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

    /* Possible weaknesses found:
     *  Assuming that condition 'i<=64' is not redundant
     */
    for (unsigned long long i = 1; i <= 64; i++) {
        /* Possible weaknesses found:
         *  Shift
         *  Shifting 64-bit value by 64 bits is undefined behaviour [shiftTooManyBits]
         */
        unsigned long long term = (1ULL << i) - 1;
        if (term != 0 && i > n / term) {
            break;
        }
        unsigned long long product = i * term;
        if (product == n) {
            return true;
        }
        if (term == 0) {
            break;
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