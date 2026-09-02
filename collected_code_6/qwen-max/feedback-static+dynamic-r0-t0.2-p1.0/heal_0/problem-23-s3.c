#include <stdio.h>
#include <stdlib.h>

int max(int a, int b) {
    return (a > b) ? a : b;
}

int findMaxSumList(int **lists, int *sizes, int numLists) {
    int maxSum = 0;
    for (int i = 0; i < numLists; ++i) {
        int sum = 0;
        for (int j = 0; j < sizes[i]; ++j) {
            sum += lists[i][j];
        }
        maxSum = max(maxSum, sum);
    }
    return maxSum;
}

int main() {
    int list1[] = {1, 2, 3};
    int list2[] = {4, 5, 6, 7};
    int list3[] = {8, 9};

    int *lists[] = {list1, list2, list3};
    int sizes[] = {3, 4, 2};
    int numLists = 3;

    int result = findMaxSumList(lists, sizes, numLists);
    printf("Maximum sum of elements in a list: %d\n", result);

    return 0;
}