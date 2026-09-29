#include <stdio.h>

int maxSumOfElements(int **list, int rowCount, const int *colCount) {
    int maxSum = 0;
    for (int i = 0; i < rowCount; i++) {
        int sum = 0;
        for (int j = 0; j < colCount[i]; j++) {
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
    int arr1[] = {1, 2, 3, 4, 5};
    int arr2[] = {6, 7, 8, 9};
    int arr3[] = {10, 11, 12, 13, 14, 15};
    int *list[] = {arr1, arr2, arr3};

    int result = maxSumOfElements(list, rowCount, colCount);
    printf("Maximum sum of elements: %d\n", result);

    return 0;
}