#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

long long safe_multiply(int a, int b) {
    if (a > 0) {
        if (b > 0) {
            if (a > INT_MAX / b) abort();
        } else {
            if (b < INT_MIN / a) abort();
        }
    } else {
        if (b > 0) {
            if (a < INT_MIN / b) abort();
        } else {
            if (a != 0 && b < INT_MAX / a) abort();
        }
    }
    return (long long)a * b;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000003,time:4,execs:15,op:(null),pos:0; likely memory-safety defect
  */

int main(void) {
    int a = 0;
    int b = 0;

    if (scanf("%d", &a) != 1) {
        abort();
    }
    if (scanf("%d", &b) != 1) {
        abort();
    }

    int product = (int)safe_multiply(a, b);
    printf("%d\n", product);

    return 0;
}