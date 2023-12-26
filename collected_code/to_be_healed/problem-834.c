#include <stdio.h>

void generateMatrix(int n) {
    int matrix[n][n];
    int num = 1, row_start = 0, row_end = n - 1, col_start = 0, col_end = n - 1;
  
    while (num <= n * n) {
        for (int i = col_start; i <= col_end; ++i)
            matrix[row_start][i] = num++;       
        row_start++;

        for (int i = row_start; i <= row_end; ++i)
            matrix[i][col_end] = num++;
        col_end--;

        for (int i = col_end; i >= col_start; --i)
            matrix[row_end][i] = num++;
        row_end--;

        for (int i = row_end; i >= row_start; --i)
            matrix[i][col_start] = num++;
        col_start++;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            /* Possible weaknesses found:
             *  Cannot determine that 'matrix[i][j]' is initialized [premium-bughuntingUninit]
             */
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int n;
    printf("Enter the value of n: ");
    /* Possible weaknesses found:
     *  Cannot determine that 'n' is initialized [premium-bughuntingUninit]
     */
    scanf("%d", &n);

    generateMatrix(n);
    
    return 0;
}