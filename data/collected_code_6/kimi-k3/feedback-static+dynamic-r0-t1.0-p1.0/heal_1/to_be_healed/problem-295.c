#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

long long sum_divisors(long long n) {
    if (n <= 0) {
        return 0;
    }
    
    long long sum = 0;
    long long i;
    
    for (i = 1; i <= n / i; i++) {
        if (n % i == 0) {
            sum += i;
            if (i != n / i) {
                sum += n / i;
            }
        }
    }
    
    return sum;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000000,time:17910,execs:1393,op:havoc,rep:8; likely memory-safety defect
  */

int main(void) {
    long long number;
    
    if (scanf("%lld", &number) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    printf("%lld\n", sum_divisors(number));
    
    return EXIT_SUCCESS;
}