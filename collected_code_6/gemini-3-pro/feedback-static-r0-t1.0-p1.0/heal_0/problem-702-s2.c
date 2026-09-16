#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int min_elements_to_remove(int arr[], int n, int k) {
    if (n == 0) return 0;
    
    qsort(arr, n, sizeof(int), compare);
    
    int max_len = 0;
    int i = 0;
    int j = 0;
    
    while (j < n) {
        if (arr[j] - arr[i] <= k) {
            if (j - i + 1 > max_len) {
                max_len = j - i + 1;
            }
            j++;
        } else {
            i++;
        }
    }
    
    return n - max_len;
}

int main(void) {
    int arr[] = {1, 3, 4, 9, 10, 11, 12, 17, 20};
    int n = sizeof(arr) / sizeof(arr[0]);
    int k = 4;
    
    int result = min_elements_to_remove(arr, n, k);
    printf("%d\n", result);
    
    return 0;
}