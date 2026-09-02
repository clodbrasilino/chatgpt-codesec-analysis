#include <stdio.h>
#include <stdlib.h>

struct MinMax {
    int min;
    int max;
};

struct MinMax findSmallestRange(int arr[][3], int n, int k) {
    int range = __INT_MAX__;
    struct MinMax result;
    
    int minHeap[n];
    for (int i = 0; i < k; i++)
        minHeap[i] = arr[i][0];
    
    int maxInMinHeap = 0;
    for (int i = 0; i < k; i++)
        if (maxInMinHeap < arr[i][0])
            maxInMinHeap = arr[i][0];

    int j[k];
    for (int i = 0; i < k; i++)
        j[i] = 0;

    while (1) {
        int currentMin = 0, currentMax = 0;
        /* Possible weaknesses found:
         *  Variable 'currentRange' is assigned a value that is never used. [unreadVariable]
         */
        int currentRange = __INT_MAX__;

        for (int i = 0; i < k; i++) {
            if (currentMin > minHeap[i]) {
                currentMin = minHeap[i];
                currentMax = arr[i][j[i] + 1];
            }
        }

        if (currentMax - currentMin < range) {
            range = currentMax - currentMin;
            result.min = currentMin;
            result.max = currentMax;
        }

        int index = 0;
        for (int i = 1; i < k; i++) {
            if (minHeap[index] > minHeap[i])
                index = i;
        }

        j[index]++;
        if (j[index] == n)
            break;

        minHeap[index] = arr[index][j[index]];
        if (minHeap[index] > maxInMinHeap)
            maxInMinHeap = minHeap[index];
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