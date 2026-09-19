#include <stdio.h>
#include <math.h>

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
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000002,time:302,execs:386,op:havoc,rep:4; likely memory-safety defect
  */

int main(void) {
    long long val;
    if (scanf("%lld", &val) == 1) {
        if (is_perfect_square(val)) {
            printf("True\n");
        } else {
            printf("False\n");
        }
    }
    return 0;
}