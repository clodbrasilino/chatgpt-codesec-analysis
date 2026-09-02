#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int countPairsWithDifference(int arr[], int n, int k) {
    qsort(arr, n, sizeof(int), compare);
    
    int count = 0;
    int i = 0, j = 1;
    
    while (j < n) {
        int diff = arr[j] - arr[i];
        
        if (diff == k) {
            count++;
            i++;
            j++;
            while (j < n && arr[j] == arr[j - 1]) j++;
            while (i < j && arr[i] == arr[i - 1]) i++;
        } else if (diff < k) {
            j++;
        } else {
            i++;
            if (i == j) j++;
        }
    }
    
    return count;
}

int main(void) {
    int arr[] = {1, 5, 3, 4, 2};
    int n = sizeof(arr) / sizeof(arr[0]);
    int k = 3;
    
    int result = countPairsWithDifference(arr, n, k);
    printf("%d\n", result);
    
    int arr2[] = {8, 12, 16, 4, 0, 20};
    int n2 = sizeof(arr2) / sizeof(arr2[0]);
    int k2 = 4;
    
    int result2 = countPairsWithDifference(arr2, n2, k2);
    printf("%d\n", result2);
    
    int arr3[] = {1, 1, 1, 1};
    int n3 = sizeof(arr3) / sizeof(arr3[0]);
    int k3 = 0;
    
    int result3 = countPairsWithDifference(arr3, n3, k3);
    printf("%d\n", result3);
    
    return 0;
}