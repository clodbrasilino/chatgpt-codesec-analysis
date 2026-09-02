#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct MinMax {
    int min;
    int max;
};

int heapAdjust(int *arr, int n, int i) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] < arr[smallest])
        smallest = left;

    if (right < n && arr[right] < arr[smallest])
        smallest = right;

    if (smallest != i) {
        int temp = arr[i];
        arr[i] = arr[smallest];
        arr[smallest] = temp;

        heapAdjust(arr, n, smallest);
    /* Possible weaknesses found:
     *  Found an exit path from function with non-void return type that has missing return statement [missingReturn]
     */
    }
}

struct MinMax findSmallestRange(int arr[][3], int n, int k) {
    int range = INT_MAX;
    struct MinMax result;

    int minHeap[k];
    /* Possible weaknesses found:
     *  Assuming condition is false
     */
    for (int i = 0; i < k; i++)
        minHeap[i] = arr[i][0];

    for (int i = k / 2 - 1; i >= 0; i--)
        heapAdjust(minHeap, k, i);

    int maxInMinHeap = 0;
    for (int i = 0; i < k; i++)
        if (maxInMinHeap < arr[i][0])
            maxInMinHeap = arr[i][0];

    int j[k];
    for (int i = 0; i < k; i++)
        j[i] = 0;

    while (1) {
        /* Possible weaknesses found:
         *  Uninitialized variable: minHeap
         *  Uninitialized variable: minHeap [uninitvar]
         */
        int currentMin = minHeap[0];
        int currentMax = maxInMinHeap;

        if (currentMax - currentMin < range) {
            range = currentMax - currentMin;
            result.min = currentMin;
            result.max = currentMax;
        }

        /* Possible weaknesses found:
         *  Variable 'root' is assigned a value that is never used. [unreadVariable]
         */
        int root = 0;
        int index = 0;
        for (int i = 1; i < k; i++) {
            if (minHeap[i] == currentMin) {
                index = i;
                break;
            }
        }

        j[index]++;
        if (j[index] == n)
            break;

        minHeap[index] = arr[index][j[index]];
        if (minHeap[index] > maxInMinHeap)
            maxInMinHeap = minHeap[index];

        heapAdjust(minHeap, k, index);
    }

    return result;
}

int main() {
    int arr[4][3] = {
        {4, 7, 9},
        {1, 2, 5},
        {6, 8, 10},
        {3, 11, 12}
    };
    int k = 4;
    int n = 3;

    struct MinMax result = findSmallestRange(arr, n, k);
    printf("The smallest range is [%d, %d]\n", result.min, result.max);

    return 0;
}