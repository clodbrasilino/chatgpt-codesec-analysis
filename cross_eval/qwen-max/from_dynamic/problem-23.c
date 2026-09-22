#include <stdio.h>
#include <stdlib.h>

int max(int a, int b) {
    return (a > b) ? a : b;
}

int findMaxSumOfList(int *list, int size) {
    int sum = 0;
    for (int i = 0; i < size; ++i) {
        sum += list[i];
    }
    return sum;
}

int findMaxSumOfLists(int **lists, int *sizes, int listsSize) {
    int maxSum = 0;
    for (int i = 0; i < listsSize; ++i) {
        int currentSum = findMaxSumOfList(lists[i], sizes[i]);
        maxSum = max(maxSum, currentSum);
    }
    return maxSum;
}

int main() {
    int listsSizes[] = {3, 2, 4};
    int numLists = sizeof(listsSizes) / sizeof(listsSizes[0]);

    int *lists[numLists];
    lists[0] = (int[]){1, 2, 3};
    lists[1] = (int[]){4, 5};
    lists[2] = (int[]){6, 7, 8, 9};

    int result = findMaxSumOfLists((int **)lists, listsSizes, numLists);
    printf("The maximum sum of elements in the list of lists is: %d\n", result);

    return 0;
}