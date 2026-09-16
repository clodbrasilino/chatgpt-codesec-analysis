#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

long long maxProduct(int *arr, int n) {
    qsort(arr, n, sizeof(int), compare);

    int max1 = arr[n-1], max2 = arr[n-2], max3 = arr[n-3];
    int min1 = arr[0], min2 = arr[1];

    return (max1 * max2 * max3 > max1 * min1 * min2) ? 
           (long long)max1 * max2 * max3 : (long long)max1 * min1 * min2;
}

int main() {
    int arr[] = {1, 2, 3, 4, -5, -6, 7, 8, 9};
    int n = sizeof(arr) / sizeof(arr[0]);

    long long result = maxProduct(arr, n);
    printf("Maximum product of three numbers: %lld\n", result);

    return 0;
}