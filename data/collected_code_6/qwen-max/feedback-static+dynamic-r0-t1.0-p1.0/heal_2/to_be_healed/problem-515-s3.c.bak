#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_SIZE 100

bool isSubsetSumDivisible(const int *arr, int n, int m) {
    int i, j;
    /* Possible weaknesses found:
     * UBSan: variable length array bound evaluates to non-positive value 0 (AFL crash: id:000004,sig:06,src:000002,time:579,execs:160,op:havoc,rep:2)
     */
    bool table[n + 1][m];
    for (i = 0; i < n + 1; i++) {
        table[i][0] = true;
    }
    for (i = 1; i < m; i++) {
        /* Possible weaknesses found:
         * ASan: dynamic-stack-buffer-overflow (AFL crash: id:000004,sig:06,src:000002,time:579,execs:160,op:havoc,rep:2)
         */
        table[0][i] = false;
    }
    for (i = 1; i < n + 1; i++) {
        for (j = 0; j < m; j++) {
            if (table[i - 1][j]) {
                table[i][j] = true;
            } else {
                /* Possible weaknesses found:
                 * UBSan: index -3 out of bounds for type 'bool[m]' (AFL crash: id:000005,sig:06,src:000002,time:3391,execs:736,op:havoc,rep:2)
                 */
                table[i][j] = table[i - 1][(j - arr[i-1] + m) % m];
            }
        }
    }
    return table[n][0];
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000002,time:13,execs:10,op:(null),pos:0; likely memory-safety defect
  */

int main() {
    int arr[MAX_SIZE], n, m;
    printf("Enter the number of elements: ");
    scanf("%d", &n);
    printf("Enter the elements: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    printf("Enter the divisor m: ");
    scanf("%d", &m);
    if (isSubsetSumDivisible(arr, n, m)) {
        printf("There is a subset with sum divisible by %d.\n", m);
    } else {
        printf("No subset has a sum divisible by %d.\n", m);
    }
    return 0;
}