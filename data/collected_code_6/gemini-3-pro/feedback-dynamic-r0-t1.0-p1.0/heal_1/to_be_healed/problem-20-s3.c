#include <stdio.h>
#include <stdbool.h>

bool isWoodall(unsigned long long n) {
    if (n < 1) {
        return false;
    }

    if (n == 1) {
        return true;
    }

    unsigned long long W = 1;
    unsigned int p = 1;

    while (W < n) {
        W = p * (1ULL << p) - 1;
        if (W == n) {
            return true;
        }
        p++;
    }

    return false;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000001,time:5495,execs:610,op:havoc,rep:4; likely memory-safety defect
  */

int main(void) {
    unsigned long long number;

    if (scanf("%llu", &number) != 1) {
        return 1;
    }

    if (isWoodall(number)) {
        printf("%llu is a Woodall number.\n", number);
    } else {
        printf("%llu is not a Woodall number.\n", number);
    }

    return 0;
}