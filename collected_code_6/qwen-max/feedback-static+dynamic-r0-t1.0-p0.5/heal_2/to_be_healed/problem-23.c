#include <stdio.h>
#include <stdlib.h>

int max(int a, int b) {
    return (a > b) ? a : b;
}

int findMaxSumList(int** lists, int listCount, const int* listSizes) {
    int maxSum = 0;
    for (int i = 0; i < listCount; ++i) {
        int currentSum = 0;
        for (int j = 0; j < listSizes[i]; ++j) {
            currentSum += lists[i][j];
        }
        maxSum = max(maxSum, currentSum);
    }
    return maxSum;
}

int main() {
    int listCount = 3;
    const int* listSizes = (const int*)malloc(listCount * sizeof(int));
    int** lists = (int**)malloc(listCount * sizeof(int*));

    /* Possible weaknesses found:
     *  read-only variable is not assignable
     *  assignment of read-only location '*listSizes'
     */
    listSizes[0] = 4;
    lists[0] = (int*)malloc(listSizes[0] * sizeof(int));
    lists[0][0] = 1;
    lists[0][1] = 2;
    lists[0][2] = 3;
    lists[0][3] = 4;

    /* Possible weaknesses found:
     *  read-only variable is not assignable
     *  assignment of read-only location '*(listSizes + 4)'
     */
    listSizes[1] = 3;
    lists[1] = (int*)malloc(listSizes[1] * sizeof(int));
    lists[1][0] = 5;
    lists[1][1] = 6;
    lists[1][2] = 7;

    /* Possible weaknesses found:
     *  read-only variable is not assignable
     *  assignment of read-only location '*(listSizes + 8)'
     */
    listSizes[2] = 2;
    lists[2] = (int*)malloc(listSizes[2] * sizeof(int));
    lists[2][0] = 8;
    lists[2][1] = 9;

    int maxSum = findMaxSumList(lists, listCount, listSizes);

    printf("Maximum sum of elements in a list: %d\n", maxSum);

    for (int i = 0; i < listCount; ++i) {
        free(lists[i]);
    }
    free(lists);
    free((void*)listSizes);

    return 0;
}