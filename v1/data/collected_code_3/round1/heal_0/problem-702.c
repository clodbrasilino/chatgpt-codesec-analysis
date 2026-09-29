#include <stdio.h>
#include <stdlib.h>

int compare(const void * a, const void * b) {
    return (*(int*)a - *(int*)b);
}

int minRemovals(int arr[], int n, int k) {
    qsort(arr, n, sizeof(int), compare);
    int removals = n - 1;
    for (int i = 0; i < n; i++) {
        int j = i + 1;
        while (j < n && arr[j] - arr[i] <= k) {
            j++;
        }
        removals = removals < (n - (j - i)) ? removals : (n - (j - i));
    }
    return removals;
}

int main() {
    int arr[] = {1, 3, 4, 9, 10, 11, 12, 17, 20};
    int n = sizeof(arr) / sizeof(arr[0]);
    int k = 4;
    printf("Minimum number of removals = %d\n", minRemovals(arr, n, k));
    return 0;
}