#include <stdio.h>

long long count_rectangles_in_circle(long long r);

long long count_rectangles_in_circle(long long r) {
    if (r <= 0) {
        return 0;
    }

    long long count = 0;
    long long r_squared = r * r;

    for (long long x = 0; (x + 1) * (x + 1) <= r_squared; ++x) {
        for (long long y = 0; (x + 1) * (x + 1) + (y + 1) * (y + 1) <= r_squared; ++y) {
            count++;
        }
    }

    return count * 4;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000000,time:13,execs:21,op:havoc,rep:5; likely memory-safety defect
  */

int main(void) {
    long long r = 0;
    
    if (scanf("%lld", &r) != 1) {
        return 1;
    }

    long long result = count_rectangles_in_circle(r);
    
    if (printf("%lld\n", result) < 0) {
        return 1;
    }

    return 0;
}