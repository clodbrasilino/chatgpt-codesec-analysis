#include <stdio.h>
#include <stdlib.h>

long long findNumber(long long x) {
    if (x <= 0) {
        return -1; 
    }
    
    long long n = 1;
    long long fact = 1;

    while (n <= x) {
        fact = (fact * n) % x;
        if (fact == 0) {
            return n;
        }
        n++;
    }
    
    return n;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000000,time:8234,execs:603,op:havoc,rep:8; likely memory-safety defect
  */

int main(void) {
    long long x = 0;
    
    if (scanf("%lld", &x) != 1) {
        return EXIT_FAILURE;
    }
    
    if (x <= 0) {
        return EXIT_FAILURE;
    }
    
    long long result = findNumber(x);
    if (result != -1) {
        printf("%lld\n", result);
    }
    
    return EXIT_SUCCESS;
}