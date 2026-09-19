#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 2, got 1
  *  test case 2 failed: expected 3, got 4
  *  test case 0 failed: expected 924, got 8680820740569208054
  */

long rencontres_number(int n, int k) {
    long *D = (long *)malloc((n + 1) * (k + 1) * sizeof(long));
    if (!D) {
        return -1;
    }
    for (int i = 0; i <= n; ++i) {
        D[i * (k + 1)] = 1;
        if (i == 1) {
            D[i * (k + 1) + 1] = 0;
        }
    }
    for (int j = 0; j <= k; ++j) {
        D[j] = (j % 2 == 0) ? 1 : -1;
    }

    for (int i = 2; i <= n; ++i) {
        for (int j = 1; j <= k; ++j) {
            /* Possible weaknesses found:
             * UBSan: signed integer overflow: 6546424788311810324 + 6613313319248080000 cannot be represented in type 'long' (AFL crash: id:000001,sig:06,src:000001,time:813,execs:358,op:havoc,rep:7)
             * UBSan: signed integer overflow: 2 * -4702111234474983745 cannot be represented in type 'long' (AFL crash: id:000001,sig:06,src:000001,time:813,execs:358,op:havoc,rep:7)
             */
            D[i * (k + 1) + j] = (i - 1) * (D[(i - 1) * (k + 1) + j] + D[(i - 1) * (k + 1) + j - 1]);
        }
    }
    
    long result = D[n * (k + 1) + k];
    free(D);
    return result;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000001,time:390,execs:184,op:havoc,rep:8; likely memory-safety defect
  */

int main() {
    int n, k;
    printf("Enter n and k: ");
    if (scanf("%d %d", &n, &k) != 2) {
        printf("Invalid input\n");
        return 1;
    }

    long result = rencontres_number(n, k);
    if (result == -1) {
        printf("Memory allocation failed\n");
        return 1;
    }

    printf("The %d-th Rencontres Number is: %ld\n", n, result);
    return 0;
}