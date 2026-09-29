#include <stdio.h>
#include <stdlib.h>

int maxSum(int **list, int rows, int cols) {
    int maxSum = 0;
    for(int i = 0; i < rows; i++) {
        int rowSum = 0;
        for(int j = 0; j < cols; j++) {
            rowSum += list[i][j];
        }
        if(rowSum > maxSum) {
            maxSum = rowSum;
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

    /* Possible weaknesses found:
     *  dereference of possibly-NULL '*list' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
    list[0][0] = 1; list[0][1] = 2; list[0][2] = 3;
    /* Possible weaknesses found:
     *  dereference of possibly-NULL '*list_43 + 8' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
    list[1][0] = 4; list[1][1] = 5; list[1][2] = 6;
    /* Possible weaknesses found:
     *  dereference of possibly-NULL '*list_43 + 16' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
    list[2][0] = 7; list[2][1] = 8; list[2][2] = 9;

    printf("Max sum: %d\n", maxSum(list, rows, cols));

    for(int i = 0; i < rows; i++) {
        free(list[i]);
    }
    free(list);

    return 0;
}