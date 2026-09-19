#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_SIZE 100

bool isSubsetSumDivisible(const int *arr, int n, int m) {
    if (m <= 0) return false;

    /* Possible weaknesses found:
     * UBSan: signed integer overflow: -957633962 * 137333333 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000000,time:2047,execs:1818,op:havoc,rep:7)
     * ASan: requested (AFL crash: id:000001,sig:06,src:000001,time:26400,execs:16842,op:havoc,rep:2)
     * UBSan: signed integer overflow: 4 * 624973163 cannot be represented in type 'int' (AFL crash: id:000001,sig:06,src:000001,time:26400,execs:16842,op:havoc,rep:2)
     */
    bool *table = malloc((n + 1) * m * sizeof(bool));
    if (!table) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(1);
    }

    for (int i = 0; i <= n; i++) {
        table[i * m] = true;
    }
    for (int i = 1; i < m; i++) {
        /* Possible weaknesses found:
         * ASan: heap-buffer-overflow (AFL crash: id:000002,sig:06,src:000001,time:55743,execs:23701,op:havoc,rep:2)
         */
        table[i] = false;
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < m; j++) {
            if (table[(i - 1) * m + j]) {
                table[i * m + j] = true;
            } else {
                int idx = (j - arr[i - 1] + m) % m;
                if (idx >= 0 && idx < m) {
                    table[i * m + j] = table[(i - 1) * m + idx];
                } else {
                    table[i * m + j] = false;
                }
            }
        }
    }

    /* Possible weaknesses found:
     * UBSan: signed integer overflow: -957633963 * 137333333 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000000,time:2047,execs:1818,op:havoc,rep:7)
     */
    bool result = table[n * m];
    free(table);
    return result;
}

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