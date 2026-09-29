#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int longest_consecutive_subsequence(int arr[], int n) {
    if (n == 0) return 0;
    
    qsort(arr, n, sizeof(int), compare);
    
    int longest = 1;
    int current = 1;
    
    for (int i = 1; i < n; i++) {
        if (arr[i] == arr[i-1])
            continue;
        else if (arr[i] == arr[i-1] + 1) {
            current++;
            if (current > longest)
                longest = current;
        } else {
            current = 1;
        }
    }
    
    return longest;
}

int main(void) {
    int arr[] = {1, 9, 3, 10, 4, 20, 2};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    int result = longest_consecutive_subsequence(arr, n);
    printf("Length of longest consecutive subsequence: %d\n", result);
    
    return 0;
}