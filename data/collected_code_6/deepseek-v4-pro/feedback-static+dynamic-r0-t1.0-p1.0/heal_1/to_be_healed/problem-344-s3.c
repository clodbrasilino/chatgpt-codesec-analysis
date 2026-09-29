#include <stdio.h>
#include <math.h>

int countOddFactorsInRange(int start, int end) {
    if (start > end) {
        return 0;
    }

    int count = 0;
    int sqrt_start = (int)sqrt((double)start);
    int sqrt_end = (int)sqrt((double)end);

    if (sqrt_start * sqrt_start < start) {
        sqrt_start++;
    }

    for (int i = sqrt_start; i <= sqrt_end; i++) {
        count++;
    }

    return count;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000002,time:640,execs:287,op:havoc,rep:1; likely memory-safety defect
  */

int main(void) {
    int start, end;

    if (scanf("%d %d", &start, &end) != 2) {
        return 1;
    }

    printf("%d\n", countOddFactorsInRange(start, end));

    return 0;
}