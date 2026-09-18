#include <stdio.h>
#include <stdlib.h>

int newman_conway(int n) {
    if (n < 1) {
        return 0;
    }
    if (n == 1 || n == 2) {
        return 1;
    }
    return newman_conway(newman_conway(n - 1)) + newman_conway(n - newman_conway(n - 1));
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:11,src:000000,time:7183,execs:136,op:havoc,rep:5; likely memory-safety defect
  */

int main(void) {
    int n;
    printf("Enter n: ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    if (n < 1) {
        fprintf(stderr, "n must be positive\n");
        return 1;
    }
    printf("%d\n", newman_conway(n));
    return 0;
}