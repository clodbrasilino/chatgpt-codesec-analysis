#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

uint64_t sum_fifth_power_even(int n) {
    uint64_t sum = 0;
    int i;
    
    if (n <= 0) {
        return 0;
    }
    
    for (i = 1; i <= n; i++) {
        uint64_t even_num = (uint64_t)(2 * i);
        uint64_t power = even_num * even_num * even_num * even_num * even_num;
        sum += power;
    }
    
    return sum;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000000,time:1495,execs:826,op:havoc,rep:6; likely memory-safety defect
  */

int main(void) {
    int n;
    
    printf("Enter the value of n: ");
    
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    
    if (n < 0) {
        fprintf(stderr, "n must be non-negative\n");
        return 1;
    }
    
    uint64_t result = sum_fifth_power_even(n);
    printf("Sum of fifth power of first %d even natural numbers: %" PRIu64 "\n", n, result);
    
    return 0;
}