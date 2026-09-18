#include <stdio.h>
#include <math.h>
#include <stdint.h>

long long countOddFactors(long long start, long long end) {
    if (start > end) {
        long long temp = start;
        start = end;
        end = temp;
    }
    
    if (end < 1) {
        return 0;
    }
    
    if (start < 1) {
        start = 1;
    }
    
    long long sqrt_end = (long long)sqrt((double)end);
    long long sqrt_start_minus_1 = (long long)sqrt((double)(start - 1));
    
    while ((sqrt_end + 1) * (sqrt_end + 1) <= end) {
        sqrt_end++;
    }
    while (sqrt_end * sqrt_end > end) {
        sqrt_end--;
    }
    
    while ((sqrt_start_minus_1 + 1) * (sqrt_start_minus_1 + 1) <= start - 1) {
        sqrt_start_minus_1++;
    }
    while (sqrt_start_minus_1 * sqrt_start_minus_1 > start - 1) {
        sqrt_start_minus_1--;
    }
    
    return sqrt_end - sqrt_start_minus_1;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000003,time:2704,execs:1070,op:havoc,rep:1; likely memory-safety defect
  */

int main(void) {
    long long start, end;
    
    if (scanf("%lld %lld", &start, &end) != 2) {
        return 1;
    }
    
    long long result = countOddFactors(start, end);
    printf("%lld\n", result);
    
    return 0;
}