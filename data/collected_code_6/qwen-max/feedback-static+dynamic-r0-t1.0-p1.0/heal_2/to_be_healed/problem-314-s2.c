#include <stdio.h>
#include <stdlib.h>

int max_sum(int *arr, int n) {
    if (n <= 0) return 0;
    if (n == 1) return arr[0] > arr[1] ? arr[0] : arr[1];

    int incl = arr[0];
    int excl = 0;
    /* Possible weaknesses found:
     *  The scope of the variable 'excl_new' can be reduced. [variableScope]
     */
    int excl_new;

    for (int i = 1; i < n; i++) {
        excl_new = (incl > excl ? incl : excl);
        incl = excl + arr[i];
        excl = excl_new;
    }
    return (incl > excl ? incl : excl);
}

int main() {
    int n;
    if (scanf("%d", &n) != 1 || n < 1) {
        return 1;
    }

    int *arr = (int *)malloc(n * sizeof(int));
    if (arr == NULL) {
        return 1;
    }

    for (int i = 0; i < n; i++) {
        if (scanf("%d", &arr[i]) != 1) {
            free(arr);
            return 1;
        }
    }

    int result = max_sum(arr, n);
    printf("%d\n", result);

    free(arr);
    return 0;
}