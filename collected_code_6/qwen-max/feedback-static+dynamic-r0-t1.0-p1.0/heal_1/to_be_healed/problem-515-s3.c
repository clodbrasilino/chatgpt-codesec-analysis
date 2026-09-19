#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_SIZE 100

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as pointer to const [constParameterPointer]
 */
bool isSubsetSumDivisible(int *arr, int n, int m) {
    int i, j;
    bool table[n + 1][m];
    for (i = 0; i < n + 1; i++) {
        table[i][0] = true;
    }
    for (i = 1; i < m; i++) {
        table[0][i] = false;
    }
    for (i = 1; i < n + 1; i++) {
        for (j = 0; j < m; j++) {
            if (table[i - 1][j]) {
                table[i][j] = true;
            } else {
                /* Possible weaknesses found:
                 * ASan: dynamic-stack-buffer-overflow (AFL crash: id:000003,sig:06,src:000002,time:231,execs:74,op:havoc,rep:2)
                 * UBSan: index -1 out of bounds for type 'bool[m]' (AFL crash: id:000003,sig:06,src:000002,time:231,execs:74,op:havoc,rep:2)
                 * UBSan: index -7 out of bounds for type 'bool[m]' (AFL crash: id:000006,sig:06,src:000002,time:1122,execs:316,op:havoc,rep:3)
                 * UBSan: index -5 out of bounds for type 'bool[m]' (AFL crash: id:000007,sig:06,src:000002,time:15734,execs:3887,op:havoc,rep:2)
                 */
                table[i][j] = table[i - 1][(j - arr[i-1] + m) % m];
            }
        }
    }
    return table[n][0];
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000002,time:12,execs:10,op:(null),pos:0; likely memory-safety defect
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