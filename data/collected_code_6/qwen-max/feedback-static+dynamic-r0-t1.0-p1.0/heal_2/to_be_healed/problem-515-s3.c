#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_SIZE 100

bool isSubsetSumDivisible(const int *arr, int n, int m) {
    if (m <= 0) return false;

    /* Possible weaknesses found:
     * UBSan: variable length array bound evaluates to non-positive value -1223331384 (AFL crash: id:000003,sig:06,src:000002,time:1779,execs:1736,op:havoc,rep:2)
     * ASan: stack-overflow (AFL crash: id:000003,sig:06,src:000002,time:1779,execs:1736,op:havoc,rep:2)
     */
    bool table[n + 1][m];
    for (int i = 0; i <= n; i++) {
        table[i][0] = true;
    }
    for (int i = 1; i < m; i++) {
        table[0][i] = false;
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < m; j++) {
            if (table[i - 1][j]) {
                table[i][j] = true;
            } else {
                int idx = (j - arr[i - 1] + m) % m;
                /* Possible weaknesses found:
                 * UBSan: index -1 out of bounds for type 'bool[m]' (AFL crash: id:000000,sig:06,src:000000,time:405,execs:398,op:havoc,rep:2)
                 * ASan: dynamic-stack-buffer-overflow (AFL crash: id:000002,sig:06,src:000000,time:1287,execs:1259,op:havoc,rep:2)
                 */
                table[i][j] = table[i - 1][idx];
            }
        }
    }

    return table[n][0];
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000001,sig:06,src:000000,time:485,execs:475,op:havoc,rep:1; likely memory-safety defect
  */

int main() {
    int arr[MAX_SIZE], n, m;
    printf("Enter the number of elements: ");
    if (scanf("%d", &n) != 1 || n > MAX_SIZE) {
        fprintf(stderr, "Invalid number of elements.\n");
        return 1;
    }
    printf("Enter the elements: ");
    for (int i = 0; i < n; i++) {
        if (scanf("%d", &arr[i]) != 1) {
            fprintf(stderr, "Invalid input.\n");
            return 1;
        }
    }
    printf("Enter the divisor m: ");
    if (scanf("%d", &m) != 1) {
        fprintf(stderr, "Invalid divisor.\n");
        return 1;
    }
    if (isSubsetSumDivisible(arr, n, m)) {
        printf("There is a subset with sum divisible by %d.\n", m);
    } else {
        printf("No subset has a sum divisible by %d.\n", m);
    }
    return 0;
}