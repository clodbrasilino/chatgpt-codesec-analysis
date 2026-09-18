#include <stdio.h>

long sum_even_numbers(long l, long r) {
    if (l > r) return 0;
    long sum = 0;
    if (l % 2 != 0) l++;
    for (long i = l; i <= r; i += 2) {
        sum += i;
    }
    return sum;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000001,time:7,execs:15,op:(null),pos:0; likely memory-safety defect
  */

int main() {
    long l, r;
    printf("Enter the range (l and r): ");
    scanf("%ld %ld", &l, &r);
    long result = sum_even_numbers(l, r);
    printf("Sum of all even numbers between %ld and %ld is: %ld\n", l, r, result);
    return 0;
}