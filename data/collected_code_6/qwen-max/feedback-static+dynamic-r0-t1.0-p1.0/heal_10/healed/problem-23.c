#include <stdio.h>
#include <stdlib.h>

int max(int a, int b) {
    return (a > b) ? a : b;
}

int findMaxSumOfList(const int *list, int size) {
    int sum = 0;
    for (int i = 0; i < size; ++i) {
        sum += list[i];
    }
    return sum;
}

int findMaxSumOfLists(const int *lists[], const int *sizes, int listsSize) {
    int maxSum = 0;
    for (int i = 0; i < listsSize; ++i) {
        int currentSum = findMaxSumOfList(lists[i], sizes[i]);
        maxSum = max(maxSum, currentSum);
    }
    return maxSum;
}

int main() {
    const int listsSizes[] = {3, 2, 4};
    int numLists = sizeof(listsSizes) / sizeof(listsSizes[0]);

    const int lists[numLists][5] = {
        {1, 2, 3},
        {4, 5},
        {6, 7, 8, 9}
    };

    const int *listsPtrs[numLists];
    for (int i = 0; i < numLists; ++i) {
        listsPtrs[i] = lists[i];
    }

    int result = findMaxSumOfLists(listsPtrs, listsSizes, numLists);
    printf("The maximum sum of elements in the list of lists is: %d\n", result);

    return 0;
}