#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <inttypes.h>

bool is_factorial_divisible(uint64_t n, uint64_t x) {
    uint64_t factorial = 1;
    uint64_t i;
    
    for (i = 1; i <= n; i++) {
        factorial *= i;
        if (factorial % x == 0) {
            return true;
        }
    }
    
    return false;
}

uint64_t find_first_natural_number(uint64_t x) {
    uint64_t n = 1;
    
    while (1) {
        if (is_factorial_divisible(n, x)) {
            return n;
        }
        n++;
    }
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000003,time:669,execs:340,op:havoc,rep:3; likely memory-safety defect
  */

int main() {
    uint64_t x;
    
    printf("Enter the value of x: ");
    scanf("%" SCNu64, &x);
    
    uint64_t result = find_first_natural_number(x);
    
    printf("The first natural number whose factorial is divisible by %" PRIu64 " is %" PRIu64 ".\n", x, result);
    
    return 0;
}