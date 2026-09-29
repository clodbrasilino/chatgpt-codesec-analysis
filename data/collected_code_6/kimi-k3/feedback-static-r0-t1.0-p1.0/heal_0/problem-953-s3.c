#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    int x = *(const int *)a;
    int y = *(const int *)b;
    return (x > y) - (x < y);
}

int find_min_subsets(int arr[], int n) {
    if (arr == NULL || n <= 0) {
        return 0;
    }
    
    qsort(arr, (size_t)n, sizeof(int), compare);
    
    int max_freq = 1;
    int current_freq = 1;
    
    for (int i = 1; i < n; i++) {
        if (arr[i] == arr[i - 1]) {
            current_freq++;
            if (current_freq > max_freq) {
                max_freq = current_freq;
            }
        } else {
            current_freq = 1;
        }
    }
    
    return max_freq;
}

int main(void) {
    int arr[] = {1, 2, 2, 3, 3, 3, 4, 4, 4, 4};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    int result = find_min_subsets(arr, n);
    printf("Minimum number of subsets: %d\n", result);
    
    return 0;
}