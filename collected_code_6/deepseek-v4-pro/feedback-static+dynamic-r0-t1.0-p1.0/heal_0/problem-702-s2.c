#include <stdio.h>
#include <stdlib.h>

static int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int minRemovals(int arr[], int n, int k) {
    qsort(arr, n, sizeof(int), compare);
    
    int maxLen = 0;
    int left = 0;
    
    for (int right = 0; right < n; right++) {
        while (arr[right] - arr[left] > k) {
            left++;
        }
        int currLen = right - left + 1;
        if (currLen > maxLen) {
            maxLen = currLen;
        }
    }
    
    return n - maxLen;
}

int main(void) {
    int arr[] = {1, 3, 4, 9, 10, 11, 12, 17, 20};
    int n = sizeof(arr) / sizeof(arr[0]);
    int k = 4;
    
    int removals = minRemovals(arr, n, k);
    printf("%d\n", removals);
    
    return 0;
}