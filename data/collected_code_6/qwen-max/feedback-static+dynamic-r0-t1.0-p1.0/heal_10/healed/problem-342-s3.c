#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct MinMax {
    int min;
    int max;
};

int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

struct MinMax findSmallestRange(int arr[][3], int n, int k) {
    struct MinMax result = { .min = INT_MAX, .max = INT_MIN };
    int range = INT_MAX;

    int minHeap[k];
    for (int i = 0; i < k; i++)
        minHeap[i] = arr[i][0];

    qsort(minHeap, k, sizeof(int), compare);

    int j[k];
    for (int i = 0; i < k; i++)
        j[i] = 0;

    while (1) {
        int currentMin = minHeap[0];
        int currentMax = minHeap[k-1];

        if (currentMax - currentMin < range) {
            range = currentMax - currentMin;
            result.min = currentMin;
            result.max = currentMax;
        }

        int index = 0;
        for (int i = 0; i < k; i++) {
            if (minHeap[i] == currentMin) {
                index = i;
                break;
            }
        }

        j[index]++;
        if (j[index] == n)
            break;

        if (j[index] < n) {
            minHeap[index] = arr[index][j[index]];
            qsort(minHeap, k, sizeof(int), compare);
        } else {
            break;
        }
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