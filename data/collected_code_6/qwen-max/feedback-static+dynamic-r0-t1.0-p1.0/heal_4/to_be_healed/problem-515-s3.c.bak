#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_SIZE 100

bool isSubsetSumDivisible(const int *arr, int n, int m) {
    if (m <= 0 || n <= 0) {
        return false;
    }
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
                int prev_idx = (j - arr[i - 1] + m) % m;
                /* Possible weaknesses found:
                 * UBSan: index -1 out of bounds for type 'bool[m]' (AFL crash: id:000002,sig:06,src:000000,time:628,execs:283,op:havoc,rep:2)
                 */
                table[i][j] = table[i - 1][prev_idx];
            }
        }
    }
    return table[n][0];
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000000,time:31,execs:22,op:havoc,rep:1; likely memory-safety defect
  */

int main() {
    int arr[MAX_SIZE], n, m;
    printf("Enter the number of elements: ");
    if (scanf("%d", &n) != 1) {
        return 1;
    }
    if (n > MAX_SIZE || n <= 0) {
        printf("Invalid number of elements.\n");
        return 1;
    }
    printf("Enter the elements: ");
    for (int i = 0; i < n; i++) {
        if (scanf("%d", &arr[i]) != 1) {
            return 1;
        }
    }
    printf("Enter the divisor m: ");
    if (scanf("%d", &m) != 1) {
        return 1;
    }
    if (isSubsetSumDivisible(arr, n, m)) {
        printf("There is a subset with sum divisible by %d.\n", m);
    } else {
        printf("No subset has a sum divisible by %d.\n", m);
    }
    return 0;
}