#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int maxPathSum(int **triangle, int numRows) {
    if (triangle == NULL || numRows <= 0) {
        return 0;
    }
    
    int *dp = (int *)malloc((size_t)numRows * sizeof(int));
    if (dp == NULL) {
        return 0;
    }
    
    if (triangle[numRows - 1] != NULL) {
        /* Possible weaknesses found:
         *  'copy_size' is assigned value '(unsigned long)numRows*sizeof(int)' here.
         */
        size_t copy_size = (size_t)numRows * sizeof(int);
        /* Possible weaknesses found:
         *  The comparison 'copy_size > (unsigned long)numRows*sizeof(int)' is always false because 'copy_size' and '(unsigned long)numRows*sizeof(int)' represent the same value.
         *  The comparison 'copy_size > (unsigned long)numRows*sizeof(int)' is always false because 'copy_size' and '(unsigned long)numRows*sizeof(int)' represent the same value. [knownConditionTrueFalse]
         */
        if (copy_size > (size_t)numRows * sizeof(int)) {
            free(dp);
            return 0;
        }
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(dp, triangle[numRows - 1], copy_size);
    } else {
        free(dp);
        return 0;
    }
    
    for (int i = numRows - 2; i >= 0; i--) {
        if (triangle[i] == NULL) {
            free(dp);
            return 0;
        }
        for (int j = 0; j <= i; j++) {
            dp[j] = triangle[i][j] + (dp[j] > dp[j + 1] ? dp[j] : dp[j + 1]);
        }
    }
    
    int result = dp[0];
    free(dp);
    dp = NULL;
    
    return result;
}

int main(void) {
    int row0[] = {3};
    int row1[] = {7, 4};
    int row2[] = {2, 4, 6};
    int row3[] = {8, 5, 9, 3};
    
    int *triangle[] = {row0, row1, row2, row3};
    int numRows = 4;
    
    int result = maxPathSum(triangle, numRows);
    
    printf("Maximum path sum: %d\n", result);
    
    return 0;
}