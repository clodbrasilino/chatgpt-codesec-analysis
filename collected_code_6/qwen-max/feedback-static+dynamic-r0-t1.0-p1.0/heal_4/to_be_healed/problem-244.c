#include <stdio.h>
#include <math.h>
#include <stdint.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 9, got 4
  *  test case 0 failed: expected 36, got 25
  */

uint64_t next_perfect_square(uint64_t n) {
    uint64_t root = (uint64_t)sqrt(n);
    if (root * root == n) {
        root += 1;
    }
    return root * root;
}

int main() {
    uint64_t number;
    printf("Enter a number: ");
    /* Possible weaknesses found:
     *  %llu in format string (no. 1) requires 'unsigned long long *' but the argument type is 'unsigned long *'. [invalidScanfArgType_int]
     */
    if (scanf("%llu", &number) != 1) {
        printf("Invalid input.\n");
        return 1;
    }
    uint64_t next_square = 0;
    if (number > 0) {
        next_square = next_perfect_square(number);
    } else {
        next_square = 1;
    }
    printf("Next perfect square: %llu\n", (unsigned long long)next_square);
    return 0;
}