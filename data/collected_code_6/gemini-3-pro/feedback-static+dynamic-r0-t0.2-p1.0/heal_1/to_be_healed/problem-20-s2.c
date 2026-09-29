#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected True, got 0
  */

bool is_woodall(unsigned long long n) {
    if (n < 1) {
        return false;
    }

    if (n % 2 == 0) {
        return false;
    }

    unsigned long long w = n + 1;
    unsigned long long p = 0;

    while (w % 2 == 0) {
        w /= 2;
        p++;
    }

    if (p == w) {
        return true;
    }

    return false;
}

int main(void) {
    unsigned long long num = 0;
    
    if (scanf("%llu", &num) != 1) {
        return EXIT_FAILURE;
    }

    if (is_woodall(num)) {
        printf("1\n");
    } else {
        printf("0\n");
    }

    return EXIT_SUCCESS;
}