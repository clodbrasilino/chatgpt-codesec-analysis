#include <stdio.h>
#include <limits.h>

void findSmallestRange(int* arr[], int numRows, int* numCols) {
    int minRange = INT_MAX;

    int ptr[numRows];

    int i, max, min, range, minIndex;

    for (i = 0; i < numRows; i++) {
        ptr[i] = 0;
    }

    while (1) {
        minIndex = -1;
        min = INT_MAX;
        max = INT_MIN;

        for (i = 0; i < numRows; i++) {
            if (ptr[i] >= numCols[i]) {
                return;
            }

            if (arr[i][ptr[i]] < min) {
                minIndex = i;
                min = arr[i][ptr[i]];
            }

            if (arr[i][ptr[i]] > max) {
                max = arr[i][ptr[i]];
            }
        }

        range = max - min;

        if (range < minRange) {
            minRange = range;
        }

        ptr[minIndex]++;

    }
}

int main() {
    int arr1[] = {4, 7, 9, 12, 15};
    int arr2[] = {0, 8, 10, 14, 20};
    int arr3[] = {6, 12, 16, 30, 50};

    int* arr[] = {arr1, arr2, arr3};
    int numRows = sizeof(arr) / sizeof(arr[0]);
    int numCols[] = {sizeof(arr1) / sizeof(arr1[0]), sizeof(arr2) / sizeof(arr2[0]), sizeof(arr3) / sizeof(arr3[0])};

    findSmallestRange(arr, numRows, numCols);

    return 0;
}