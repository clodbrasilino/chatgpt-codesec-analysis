#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int multiply(int a, int b) {
    if (b > 0) {
        if (a > INT_MAX / b) abort();
        if (a < INT_MIN / b) abort();
    } else if (b == -1) {
        if (a == INT_MIN) abort();
    } else if (b < -1) {
        if (a < INT_MAX / b) abort();
        if (a > INT_MIN / b) abort();
    }
    return a * b;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000006,time:8761,execs:4183,op:havoc,rep:3; likely memory-safety defect
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