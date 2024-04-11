#include <stdio.h>

#define MAX_LISTS 10
#define MAX_ELEMENTS 10

int* findHighestSumList(int lists[MAX_LISTS][MAX_ELEMENTS], int listSizes[MAX_LISTS], int numLists) {
    int maxSum = 0;
    int *maxList = NULL;

    for(int i = 0; i < numLists; i++) {
        int currentSum = 0;
        for(int j = 0; j < listSizes[i]; j++) {
            currentSum += lists[i][j];
        }
        if(currentSum > maxSum) {
            maxSum = currentSum;
            maxList = lists[i];
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
    int listSizes[MAX_LISTS] = {5, 5, 5, 5, 5};
    int numLists = 5;
    int *maxList = findHighestSumList(lists, listSizes, numLists);
    int index = (maxList - &lists[0][0])/MAX_ELEMENTS;

    printf("List with highest sum is: ");
    for(int i = 0; i < listSizes[index]; i++) {
        /* Possible weaknesses found:
         *  dereference of NULL 'maxList' [CWE-476] [-Wanalyzer-null-dereference]
         */
        printf("%d ", maxList[i]);
    }

    return 0;
}