#include <stdio.h>

int is_isosceles(int a, int b, int c) {
    if (a <= 0 || b <= 0 || c <= 0) {
        return 0;
    }
    if (a + b <= c || b + c <= a || a + c <= b) {
        return 0;
    }
    return (a == b || b == c || a == c);
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000007,time:12880,execs:5040,op:havoc,rep:5; likely memory-safety defect
  */

int main(void) {
    int a, b, c;
    if (scanf("%d %d %d", &a, &b, &c) != 3) {
        return 1;
    }
    if (is_isosceles(a, b, c)) {
        printf("Isosceles\n");
    } else {
        printf("Not isosceles\n");
    }
    return 0;
}