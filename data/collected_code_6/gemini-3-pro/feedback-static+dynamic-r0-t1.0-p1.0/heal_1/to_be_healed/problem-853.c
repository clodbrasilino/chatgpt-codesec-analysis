#include <stdio.h>
#include <stdlib.h>

long long sum_of_odd_factors(long long n) {
    if (n < 0) {
        n = -n;
    }
    
    if (n == 0) {
        return 0;
    }

    while (n % 2 == 0) {
        n /= 2;
    }

    long long sum = 0;
    for (long long i = 1; i * i <= n; i += 2) {
        if (n % i == 0) {
            sum += i;
            if (i * i != n) {
                sum += n / i;
            }
        }
    }
    
    return sum;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000001,time:691,execs:361,op:havoc,rep:3; likely memory-safety defect
  */

int main(void) {
    long long num = 0;

    if (scanf("%lld", &num) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    long long result = sum_of_odd_factors(num);
    printf("%lld\n", result);

    return EXIT_SUCCESS;
}