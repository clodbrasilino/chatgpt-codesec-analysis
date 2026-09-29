#include <stdio.h>
#include <math.h>
#include <stdint.h>
#include <inttypes.h>

int64_t sum_of_odd_factors(int64_t n) {
    int64_t sum = 0;
    int64_t limit = (int64_t)sqrt((double)n);
    
    for (int64_t i = 1; i <= limit; i++) {
        if (n % i == 0) {
            if (i % 2 == 1) {
                sum += i;
            }
            
            int64_t paired_factor = n / i;
            if (paired_factor != i && paired_factor % 2 == 1) {
                sum += paired_factor;
            }
        }
    }
    
    return sum;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000000,time:6636,execs:885,op:havoc,rep:11; likely memory-safety defect
  */

int main(void) {
    int64_t number;
    
    printf("Enter a number: ");
    if (scanf("%" SCNd64, &number) != 1 || number <= 0) {
        printf("Invalid input\n");
        return 1;
    }
    
    int64_t result = sum_of_odd_factors(number);
    printf("Sum of odd factors: %" PRId64 "\n", result);
    
    return 0;
}