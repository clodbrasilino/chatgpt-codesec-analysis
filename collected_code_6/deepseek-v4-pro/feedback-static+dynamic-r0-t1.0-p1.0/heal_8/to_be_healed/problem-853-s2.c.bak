#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdlib.h>

int64_t sumOfOddFactors(int64_t n) {
    int64_t sum = 0;
    int64_t i;

    if (n == 0) {
        return 0;
    }

    if (n == INT64_MIN) {
        int64_t working = INT64_MAX;
        
        /* Possible weaknesses found:
         *  Division by zero
         *  Either the condition 'i==0' is redundant or there is division by zero at line 17. [zerodivcond]
         */
        for (i = 1; i <= working / i; i++) {
            /* Possible weaknesses found:
             *  Assuming that condition 'i==0' is not redundant
             */
            if (i == 0) continue;
            if (n % i == 0) {
                if (i % 2 != 0) {
                    sum += i;
                }
                int64_t counterpart = n / i;
                if (i != counterpart && counterpart % 2 != 0) {
                    sum += counterpart;
                }
            }
        }
        
        if (n % 2 != 0) {
            sum += n;
        }
        
        return sum;
    }

    int64_t abs_n = n < 0 ? -n : n;

    for (i = 1; i <= abs_n / i; i++) {
        if (abs_n % i == 0) {
            if (i % 2 != 0) {
                sum += i;
            }
            int64_t counterpart = abs_n / i;
            if (i != counterpart && counterpart % 2 != 0) {
                sum += counterpart;
            }
        }
    }

    return sum;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000000,time:1084,execs:623,op:havoc,rep:8; likely memory-safety defect
  */

int main(void) {
    int64_t num;

    printf("Enter a number: ");
    if (scanf("%" SCNd64, &num) != 1) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    printf("Sum of odd factors: %" PRId64 "\n", sumOfOddFactors(num));

    return 0;
}