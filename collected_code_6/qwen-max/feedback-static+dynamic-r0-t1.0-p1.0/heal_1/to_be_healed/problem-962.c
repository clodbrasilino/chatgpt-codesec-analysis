#include <stdio.h>

long sum_of_evens(long l, long r) {
    long sum = 0;
    if (l % 2 != 0) l++;
    for (long i = l; i <= r; i += 2) {
        sum += i;
    }
    return sum;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000001,time:8,execs:15,op:(null),pos:0; likely memory-safety defect
  */

int main() {
    long l, r;
    printf("Enter the range (l r): ");
    scanf("%ld %ld", &l, &r);
    if (l > r) {
        printf("Invalid range. Please ensure l is less than or equal to r.\n");
        return 1;
    }
    long result = sum_of_evens(l, r);
    printf("Sum of even numbers between %ld and %ld: %ld\n", l, r, result);
    return 0;
}