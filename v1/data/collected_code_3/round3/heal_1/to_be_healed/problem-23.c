#include <stdio.h>
#include <stdlib.h>

int maxSum(int **arr, int n, int m) {
    int max_sum = 0;
    for(int i = 0; i < n; i++) {
        int sum = 0;
        for(int j = 0; j < m; j++) {
            sum += arr[i][j];
        }
        if(sum > max_sum) {
            max_sum = sum;
        }
    }
    return max_sum;
}

int main() {
    int n = 3, m = 3;
    int **arr = (int **)malloc(n * sizeof(int *));
    for(int i = 0; i < n; i++) {
        /* Possible weaknesses found:
         *  dereference of possibly-NULL 'arr' [CWE-690] [-Wanalyzer-possible-null-dereference]
         */
        arr[i] = (int *)malloc(m * sizeof(int));
    }
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            scanf("%d", &arr[i][j]);
        }
    }
    printf("%d\n", maxSum(arr, n, m));
    for(int i = 0; i < n; i++) {
        free(arr[i]);
    }
    free(arr);
    return 0;
}