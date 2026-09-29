#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected False, got <no output>
  *  test case 0 failed: expected True, got <no output>
  *  test case 2 failed: expected False, got <no output>
  */

bool is_woodall(unsigned long long n) {
    if (n < 1) {
        return false;
    }

    if (n == 1) {
        return true;
    }

    unsigned long long w = 0;
    unsigned long long i = 1;

    while (w < n) {
        w = i * (1ULL << i) - 1;
        if (w == n) {
            return true;
        }
        i++;
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