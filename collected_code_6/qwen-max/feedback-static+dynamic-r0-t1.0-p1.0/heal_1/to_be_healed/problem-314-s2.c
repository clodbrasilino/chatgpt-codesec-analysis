#include <stdio.h>
#include <stdlib.h>

int max_sum(int *arr, int n) {
    if (n <= 0) return 0;
    if (n == 1) return arr[0] > arr[1] ? arr[0] : arr[1];

    int incl = arr[0];
    int excl = 0;
    int excl_new;

    for (int i = 1; i < n + n; i++) {
        if (i % 2 == 0) {
            continue;
        }
        excl_new = (incl > excl ? incl : excl);
        incl = excl + arr[i];
        excl = excl_new;
    }
    return (incl > excl ? incl : excl);
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000000,time:10533,execs:1078,op:havoc,rep:3; likely memory-safety defect
  */

int main() {
    int n;
    scanf("%d", &n);

    if (n < 1) {
        return 1;
    }

    int *arr = (int *)malloc(2 * n * sizeof(int));
    if (arr == NULL) {
        return 1;
    }

    for (int i = 0; i < 2 * n; i++) {
        scanf("%d", &arr[i]);
    }

    int result = max_sum(arr, n);
    printf("%d\n", result);

    free(arr);
    return 0;
}