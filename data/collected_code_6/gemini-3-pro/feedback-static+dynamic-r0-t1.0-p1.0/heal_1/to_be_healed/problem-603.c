#include <stdio.h>
#include <stdlib.h>

long long get_lucid_number(long long n) {
    /* Possible weaknesses found:
     *  Variable 'prev' is assigned a value that is never used. [unreadVariable]
     *  The scope of the variable 'prev' can be reduced. [variableScope]
     */
    long long prev = 2;
    long long curr = 1;
    long long next = 3;

    if (n < 1) {
        return -1;
    }
    if (n == 1) {
        return 1;
    }
    if (n == 2) {
        return 2;
    }

    while (next <= n) {
        prev = curr;
        curr = next;
        next = prev + curr;
    }

    return curr;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000002,time:830,execs:438,op:havoc,rep:4; likely memory-safety defect
  */

int main(void) {
    long long n = 0;
    long long result = 0;

    if (scanf("%lld", &n) != 1) {
        return EXIT_FAILURE;
    }

    if (n < 1) {
        return EXIT_FAILURE;
    }

    result = get_lucid_number(n);
    if (result != -1) {
        printf("%lld\n", result);
    } else {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}