#include <stdio.h>
#include <math.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected True, got <no output>
  *  test case 2 failed: expected False, got <no output>
  *  test case 0 failed: expected False, got <no output>
  */

int is_perfect_square(long long num) {
    if (num < 0) {
        return 0;
    }
    if (num == 0) {
        return 1;
    }
    long long sqrt_floor = (long long)sqrt((double)num);
    while (sqrt_floor * sqrt_floor > num) {
        sqrt_floor--;
    }
    while ((sqrt_floor + 1) * (sqrt_floor + 1) <= num) {
        sqrt_floor++;
    }
    return (sqrt_floor * sqrt_floor == num);
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000001,time:243,execs:159,op:havoc,rep:2; likely memory-safety defect
  */

int main(void) {
    long long val;
    if (scanf("%lld", &val) == 1) {
        if (is_perfect_square(val)) {
            printf("1\n");
        } else {
            printf("0\n");
        }
    }
    return 0;
}