#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <inttypes.h>
#include <stdlib.h>

bool is_factorial_divisible(uint64_t n, uint64_t x) {
    if (x == 0) {
        return false;
    }
    if (x == 1) {
        return true;
    }
    
    uint64_t remainder = 1;
    uint64_t i;
    
    for (i = 2; i <= n; i++) {
        uint64_t factor = i % x;
        if (remainder > UINT64_MAX / factor) {
            uint64_t gcd_val = remainder;
            uint64_t temp = x;
            while (temp != 0) {
                uint64_t t = temp;
                temp = gcd_val % temp;
                gcd_val = t;
            }
            remainder = remainder / gcd_val;
            uint64_t x_reduced = x / gcd_val;
            if (remainder > UINT64_MAX / factor) {
                return false;
            }
            remainder = (remainder * factor) % x_reduced;
            if (remainder == 0) {
                return true;
            }
            remainder = (remainder * gcd_val) % x;
        } else {
            remainder = (remainder * factor) % x;
        }
        
        if (remainder == 0) {
            return true;
        }
    }
    
    return false;
}

uint64_t find_first_natural_number(uint64_t x) {
    if (x == 0) {
        return 0;
    }
    if (x == 1) {
        return 1;
    }
    
    uint64_t n = 1;
    
    while (1) {
        if (is_factorial_divisible(n, x)) {
            return n;
        }
        n++;
    }
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000000,time:247,execs:88,op:havoc,rep:2; likely memory-safety defect
  */

int main(void) {
    uint64_t x;
    
    printf("Enter the value of x: ");
    /* Possible weaknesses found:
     * Flawfinder scanf: The scanf() family's %s operation, without a limit specification, permits buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a different input function. If the scanf format is influenceable by an attacker, it's exploitable. (risk 4, buffer)
     */
    if (scanf("%" SCNu64, &x) != 1) {
        return 1;
    }
    
    uint64_t result = find_first_natural_number(x);
    
    printf("The first natural number whose factorial is divisible by %" PRIu64 " is %" PRIu64 ".\n", x, result);
    
    return 0;
}