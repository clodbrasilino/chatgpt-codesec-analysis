#include <stdio.h>
#include <stdlib.h>

int compare(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

int findMinSum(int arr1[], int arr2[], int n) {
    qsort(arr1, n, sizeof(int), compare);
    qsort(arr2, n, sizeof(int), compare);

    int sum = 0;
    for (int i = 0; i < n; i++)
        sum = sum + abs(arr1[i] - arr2[i]);

    return sum;
}

int main() {
    int arr1[] = {3, 1, 4, 2, 6};
    int arr2[] = {7, 5, 4, 6, 3};
    int n = sizeof(arr1) / sizeof(arr1[0]);
    printf("%d\n", findMinSum(arr1, arr2, n));
    return 0;
}