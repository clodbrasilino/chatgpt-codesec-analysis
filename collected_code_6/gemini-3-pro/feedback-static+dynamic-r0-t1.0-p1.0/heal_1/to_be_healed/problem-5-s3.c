#include <stdio.h>
#include <stdlib.h>

int countWays(int n) {
    if (n < 0) {
        return 0;
    }
    if (n % 2 != 0) {
        return 0;
    }
    if (n == 0) {
        return 1;
    }
    
    int *A = (int *)malloc((n + 1) * sizeof(int));
    int *B = (int *)malloc((n + 1) * sizeof(int));
    
    if (A == NULL || B == NULL) {
        free(A);
        free(B);
        return -1;
    }

    A[0] = 1;
    A[1] = 0;
    B[0] = 0;
    B[1] = 1;

    for (int i = 2; i <= n; i++) {
        A[i] = A[i - 2] + 2 * B[i - 1];
        B[i] = A[i - 1] + B[i - 2];
    }
    
    int result = A[n];
    
    free(A);
    free(B);
    
    return result;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000001,time:331,execs:167,op:havoc,rep:1; likely memory-safety defect
  */

int main(void) {
    int n;
    if (scanf("%d", &n) != 1) {
        return 1;
    }
    
    int ways = countWays(n);
    if (ways != -1) {
        printf("%d\n", ways);
    } else {
        return 1;
    }
    
    return 0;
}