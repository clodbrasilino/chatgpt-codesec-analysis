#include <stdio.h>
#include <stdlib.h>

int count_pairs_with_sum(int *arr, int n, int sum) {
    int count = 0;
    int *freq = (int *)calloc(2001, sizeof(int));
    
    if (freq == NULL) {
        return -1;
    }
    
    for (int i = 0; i < n; i++) {
        int complement = sum - arr[i];
        
        if (complement >= -1000 && complement <= 1000) {
            count += freq[complement + 1000];
        }
        
        if (arr[i] >= -1000 && arr[i] <= 1000) {
            freq[arr[i] + 1000]++;
        }
    }
    
    free(freq);
    return count;
}

int main(void) {
    int arr[] = {1, 5, 7, -1, 5};
    int n = sizeof(arr) / sizeof(arr[0]);
    int sum = 6;
    
    int result = count_pairs_with_sum(arr, n, sum);
    
    if (result == -1) {
        printf("Memory allocation failed\n");
        return 1;
    }
    
    printf("Number of pairs with sum %d: %d\n", sum, result);
    return 0;
}