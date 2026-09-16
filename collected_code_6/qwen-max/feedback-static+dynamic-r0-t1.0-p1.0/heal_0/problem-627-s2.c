#include <stdio.h>
#include <stdlib.h>

int findSmallestMissing(int *arr, int n) {
    int i;
    for (i = 0; i < n; ++i) {
        if (arr[i] < 0 || arr[i] >= n) {
            continue;
        }
        while (arr[i] != i && arr[i] < n && arr[arr[i]] != arr[i]) {
            int temp = arr[arr[i]];
            arr[arr[i]] = arr[i];
            arr[i] = temp;
        }
    }
    for (i = 0; i < n; ++i) {
        if (arr[i] != i) {
            return i;
        }
    }
    return n;
}

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int main() {
    int arr[] = {3, 0, 1};
    int n = sizeof(arr) / sizeof(arr[0]);
    qsort(arr, n, sizeof(int), compare);
    int missing = findSmallestMissing(arr, n);
    printf("The smallest missing number is: %d\n", missing);
    return 0;
}