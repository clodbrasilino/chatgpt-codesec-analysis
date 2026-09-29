#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    return (*(int *)b - *(int *)a);
}

int maxPairSum(int *arr, int n, int k) {
    if (n < 2 || k < 1) return 0;
    qsort(arr, n, sizeof(int), compare);
    int sum = 0;
    for (int i = 0; i < 2 * k && i + 1 < n; i += 2) {
        sum += arr[i] + arr[i + 1];
    }
    return sum;
}

int main() {
    int arr[] = {9, 4, 6, 10, 3, 5};
    int n = sizeof(arr) / sizeof(arr[0]);
    int k = 2;
    printf("%d\n", maxPairSum(arr, n, k));
    return 0;
}