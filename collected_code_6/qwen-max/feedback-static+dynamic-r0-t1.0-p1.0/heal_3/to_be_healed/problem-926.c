#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <limits.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 2, got 1
  *  test case 0 failed: expected 924, got -1
  *  test case 2 failed: expected 3, got 4
  */

int64_t rencontres_number(int n, int k) {
    if (n <= 0 || k < 0 || k > n) return -1;

    int64_t *D = (int64_t *)malloc((n + 1) * (k + 1) * sizeof(int64_t));
    if (!D) return -1;

    for (int i = 0; i <= n; ++i) {
        D[i * (k + 1)] = 1;
        if (i == 1) D[i * (k + 1) + 1] = 0;
    }

    for (int j = 0; j <= k; ++j) {
        D[j] = (j % 2 == 0) ? 1 : -1;
    }

    for (int i = 2; i <= n; ++i) {
        for (int j = 1; j <= k; ++j) {
            /* Possible weaknesses found:
             * UBSan: signed integer overflow: 2 * -4702111234474983746 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000000,sig:06,src:000001,time:381,execs:355,op:havoc,rep:16)
             */
            int64_t a = (i - 1) * D[(i - 1) * (k + 1) + j];
            int64_t b = (i - 1) * D[(i - 1) * (k + 1) + j - 1];
            /* Possible weaknesses found:
             * UBSan: signed integer overflow: -4702111234474983746 + -4702111234474983746 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000000,sig:06,src:000001,time:381,execs:355,op:havoc,rep:16)
             */
            int64_t sum = a + b;
            /* Possible weaknesses found:
             * UBSan: signed integer overflow: -4702111234474983746 + -4702111234474983746 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000000,sig:06,src:000001,time:381,execs:355,op:havoc,rep:16)
             */
            if (sum / (i - 1) != D[(i - 1) * (k + 1) + j] + D[(i - 1) * (k + 1) + j - 1]) {
                free(D);
                return -1;
            }
            D[i * (k + 1) + j] = sum;
        }
    }

    int64_t result = D[n * (k + 1) + k];
    free(D);
    return result;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000001,sig:06,src:000001,time:538,execs:487,op:havoc,rep:9; likely memory-safety defect
  */

int main() {
    int n, k;
    printf("Enter n and k: ");
    if (scanf("%d %d", &n, &k) != 2) {
        printf("Invalid input\n");
        return 1;
    }

    int64_t result = rencontres_number(n, k);
    if (result == -1) {
        printf("Memory allocation failed or overflow detected\n");
        return 1;
    }

    printf("The %d-th Rencontres Number is: %" PRId64 "\n", n, result);
    return 0;
}