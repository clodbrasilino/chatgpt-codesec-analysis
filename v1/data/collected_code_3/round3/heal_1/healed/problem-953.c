#include <stdio.h>
#include <stdlib.h>

int minSubsets(int arr[], int n) {
    int max = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }

    int* freq = (int*)calloc(max + 1, sizeof(int));
    if (freq == NULL)
        return -1;

    for (int i = 0; i < n; i++) {
        freq[arr[i]]++;
    }

    int maxFreq = 0;
    for (int i = 0; i < max + 1; i++) {
       if (freq[i] > maxFreq) {
            maxFreq = freq[i];
        }
    }

    free(freq);
    return maxFreq;
}

int main() {
    int arr[] = {1, 2, 3, 3, 4, 4, 4, 5, 5, 5, 5};
    int n = sizeof(arr) / sizeof(arr[0]);    
    int result = minSubsets(arr, n);
    
    if (result != -1)        
        printf("Minimum number of subsets with distinct elements: %d\n", result);
    else
        printf("Memory allocation failed.\n");
    
    return 0;
}