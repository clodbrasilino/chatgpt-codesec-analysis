#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool is_woodall(unsigned long long n) {
    if (n < 1) {
        return false;
    }
    
    if (n == 1) {
        return true;
    }

    unsigned long long w = 0;
    unsigned int i = 1;

    while (w < n) {
        w = i * (1ULL << i) - 1;
        if (w == n) {
            return true;
        }
        i++;
    }

    return false;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000000,time:3617,execs:601,op:havoc,rep:16; likely memory-safety defect
  */

int main(void) {
    unsigned long long num = 0;
    
    if (scanf("%llu", &num) != 1) {
        return EXIT_FAILURE;
    }

    if (is_woodall(num)) {
        printf("1\n");
    } else {
        printf("0\n");
    }

    return EXIT_SUCCESS;
}