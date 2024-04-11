#include <stdio.h>
#include <stdlib.h>

int compare(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

int minElementsToRemove(int arr[], int n, int k) {
    int i, j, min = n, temp;
    qsort(arr, n, sizeof(int), compare);
    for (i = 0; i < n; ++i) {
        for (j = n - 1; j >= i; --j) {
            if (arr[j] - arr[i] <= k) {
                temp = n - (j - i + 1);
                if (temp < min) {
                    min = temp;
                }
                break;
            }
        }
    }
    return min;
}

int main() {
    int arr[] = {1, 3, 4, 9, 10, 11, 12, 17, 20};
    int n = sizeof(arr) / sizeof(arr[0]);
    int k = 4;
    printf("Minimum number of elements to be removed is %d\n", minElementsToRemove(arr, n, k));
    return 0;
}