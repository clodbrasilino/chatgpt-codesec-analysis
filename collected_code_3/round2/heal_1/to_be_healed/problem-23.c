#include <stdio.h>
#include <stdlib.h>

int maxSum(int **list, int rows, int cols) {
    int maxSum = 0;
    for(int i = 0; i < rows; i++) {
        int sum = 0;
        for(int j = 0; j < cols; j++) {
            sum += list[i][j];
        }
        if(sum > maxSum) {
            maxSum = sum;
        }
    }
    return maxSum;
}

int main() {
    int rows = 3;
    int cols = 3;
    int **list = (int **)malloc(rows * sizeof(int *));
    for(int i = 0; i < rows; i++) {
        /* Possible weaknesses found:
         *  dereference of possibly-NULL 'list' [CWE-690] [-Wanalyzer-possible-null-dereference]
         */
        list[i] = (int *)malloc(cols * sizeof(int));
    }
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            scanf("%d", &list[i][j]);
        }
    }
    printf("%d", maxSum(list, rows, cols));
    for(int i = 0; i < rows; i++) {
        free(list[i]);
    }
    free(list);
    return 0;
}