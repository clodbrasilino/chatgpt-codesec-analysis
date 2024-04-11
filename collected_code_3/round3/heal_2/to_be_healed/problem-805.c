#include <stdio.h>

#define MAX_LISTS 10
#define MAX_ELEMENTS 10

int* findHighestSumList(int lists[MAX_LISTS][MAX_ELEMENTS], int listSize[MAX_LISTS], int numLists, int *highestSumListSize) {
    int maxSum = 0;
    int *maxList = NULL;

    for(int i = 0; i < numLists; i++) {
        int currentSum = 0;
        for(int j = 0; j < listSize[i]; j++) {
            currentSum += lists[i][j];
        }
        if(currentSum > maxSum) {
            maxSum = currentSum;
            maxList = lists[i];
            *highestSumListSize = listSize[i];
        }
    }

    return maxList;
}

int main() {
    int lists[MAX_LISTS][MAX_ELEMENTS] = {
        {1, 2, 3, 4, 5},
        {2, 3, 4, 5, 6},
        {3, 4, 5, 6, 7},
        {4, 5, 6, 7, 8},
        {5, 6, 7, 8, 9}
    };
    int listSize[MAX_LISTS] = {5, 5, 5, 5, 5};
    int numLists = 5;
    int highestSumListSize;

    int *maxList = findHighestSumList(lists, listSize, numLists, &highestSumListSize);

    printf("List with highest sum is: ");
    /* Possible weaknesses found:
     *  use of uninitialized value 'highestSumListSize' [CWE-457] [-Wanalyzer-use-of-uninitialized-value]
     */
    for(int i = 0; i < highestSumListSize; i++) {
        printf("%d ", maxList[i]);
    }

    return 0;
}