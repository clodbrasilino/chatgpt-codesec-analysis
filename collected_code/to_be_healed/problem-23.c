#include <stdio.h>

int maxSumOfElements(int **list, int rowCount, int *colCount) {
    int maxSum = 0;
    for (int i = 0; i < rowCount; i++) {
        int sum = 0;
        /* Possible weaknesses found:
         *  Cannot determine that 'colCount[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        for (int j = 0; j < colCount[i]; j++) {
            /* Possible weaknesses found:
             *  Cannot determine that 'list[i][j]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             */
            sum += list[i][j];
        }
        if (sum > maxSum) {
            maxSum = sum;
        }
    }
    return maxSum;
}

int main() {
    int rowCount = 3;
    int colCount[] = {5, 4, 6};
    int *list[] = {
        (int[]){1, 2, 3, 4, 5},
        (int[]){6, 7, 8, 9},
        (int[]){10, 11, 12, 13, 14, 15}
    };

    int result = maxSumOfElements(list, rowCount, colCount);
    printf("Maximum sum of elements: %d\n", result);

    return 0;
}