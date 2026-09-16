#include <stdio.h>
#include <stdlib.h>

void flip(int *arr, int k) {
    int temp, start = 0;
    while (start < k) {
        temp = arr[start];
        arr[start] = arr[k];
        arr[k] = temp;
        start++;
        k--;
    }
}

int findMaxIndex(int *arr, int n) {
    int mi, i;
    for (mi = 0, i = 0; i < n; ++i)
        if (arr[i] > arr[mi])
            mi = i;
    return mi;
}

void pancakeSort(int *arr, int n) {
    for (int curSize = n; curSize > 1; --curSize) {
        int maxIndex = findMaxIndex(arr, curSize);
        if (maxIndex != curSize - 1) {
            flip(arr, maxIndex);
            flip(arr, curSize - 1);
        }
    }
}

int main() {
    int arr[] = {23, 10, 20, 11, 12, 6, 7};
    int n = sizeof(arr) / sizeof(arr[0]);
    pancakeSort(arr, n);
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    return 0;
}