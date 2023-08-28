#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    return (*(int *) a - *(int *) b);
}

int minSumOfAbsDiff(int arr1[], int arr2[], int n) {
    qsort(arr1, n, sizeof(int), compare);
    qsort(arr2, n, sizeof(int), compare);
    
    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += abs(arr1[i] - arr2[i]);
    }
    
    return sum;
}

int main() {
    int arr1[] = {1, 4, 8, 10};
    int arr2[] = {2, 3, 6, 11};
    int n = sizeof(arr1) / sizeof(arr1[0]);
    
    int minSum = minSumOfAbsDiff(arr1, arr2, n);
    printf("Minimum sum of absolute differences: %d\n", minSum);
    
    return 0;
}