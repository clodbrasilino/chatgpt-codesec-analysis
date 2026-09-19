#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int multiply(int a, int b) {
    if (a > 0) {
        if (b > 0) {
            if (a > INT_MAX / b) abort();
        } else if (b < 0) {
            if (b < INT_MIN / a) abort();
        }
    } else if (a < 0) {
        if (b > 0) {
            if (a < INT_MIN / b) abort();
        } else if (b < 0) {
            if (a == INT_MIN && b == INT_MIN) abort();
            if (b < INT_MAX / a) abort();
        }
    }

    return a * b;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000003,time:546,execs:322,op:havoc,rep:1; likely memory-safety defect
  */

int main(void) {
    int a, b;

    if (scanf("%d %d", &a, &b) != 2) {
        return EXIT_FAILURE;
    }

    int res = multiply(a, b);
    printf("%d\n", res);

    return EXIT_SUCCESS;
}