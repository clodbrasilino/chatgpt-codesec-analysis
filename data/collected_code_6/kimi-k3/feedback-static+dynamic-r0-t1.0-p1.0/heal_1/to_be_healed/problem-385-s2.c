#include <stdio.h>
#include <stdlib.h>

long long perrin(int n) {
    if (n < 0) {
        return -1;
    }
    if (n == 0) {
        return 3;
    }
    if (n == 1) {
        return 0;
    }
    if (n == 2) {
        return 2;
    }
    return perrin(n - 2) + perrin(n - 3);
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:11,src:000001,time:354,execs:171,op:havoc,rep:9; likely memory-safety defect
  */

int main(void) {
    int n;
    
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    if (n < 0) {
        fprintf(stderr, "Input must be non-negative\n");
        return EXIT_FAILURE;
    }
    
    printf("%lld\n", perrin(n));
    return EXIT_SUCCESS;
}