#include <stdio.h>
#include <stdlib.h>

int cmp(const void *a, const void *b) {
    return (*(const int*)a - *(const int*)b);
}

int minRemovals(const int arr[], int n, int k) {
    if (n <= 1) return 0;
    
    int *temp = (int*)malloc(n * sizeof(int));
    if (!temp) return -1;
    
    for (int i = 0; i < n; i++) {
        temp[i] = arr[i];
    }
    
    qsort(temp, n, sizeof(int), cmp);
    
    int maxLen = 1;
    int left = 0;
    
    for (int right = 0; right < n; right++) {
        while (temp[right] - temp[left] > k) {
            left++;
        }
        if (right - left + 1 > maxLen) {
            maxLen = right - left + 1;
        }
    }
    
    free(temp);
    return n - maxLen;
}

int main(void) {
    int arr[] = {1, 3, 4, 9, 10, 11, 12, 17, 20};
    int n = sizeof(arr) / sizeof(arr[0]);
    int k = 4;
    
    int result = minRemovals(arr, n, k);
    printf("%d\n", result);
    
    int arr2[] = {1, 5, 6, 2, 8};
    int n2 = sizeof(arr2) / sizeof(arr2[0]);
    int k2 = 2;
    
    result = minRemovals(arr2, n2, k2);
    printf("%d\n", result);
    
    return 0;
}