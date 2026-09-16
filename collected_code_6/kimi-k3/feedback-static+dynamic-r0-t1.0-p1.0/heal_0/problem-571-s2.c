#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

int compare_ints(const void *a, const void *b) {
    int arg1 = *(const int *)a;
    int arg2 = *(const int *)b;
    if (arg1 < arg2) return -1;
    if (arg1 > arg2) return 1;
    return 0;
}

long long find_max_sum_disjoint_pairs(const int *arr, size_t n, int k) {
    if (arr == NULL || n < 2) {
        return 0;
    }
    
    int *sorted = malloc(n * sizeof(int));
    if (sorted == NULL) {
        return 0;
    }
    memcpy(sorted, arr, n * sizeof(int));
    qsort(sorted, n, sizeof(int), compare_ints);
    
    size_t left = 0;
    size_t right = n - 1;
    long long max_sum = LLONG_MIN;
    int found = 0;
    
    while (left < right) {
        long long current_sum = (long long)sorted[left] + (long long)sorted[right];
        
        if (current_sum <= k) {
            if (current_sum > max_sum) {
                max_sum = current_sum;
                found = 1;
            }
            left++;
        } else {
            right--;
        }
    }
    
    free(sorted);
    
    if (!found) {
        return 0;
    }
    
    return max_sum;
}

int main(void) {
    int arr[] = {5, 1, 8, 3, 9, 2};
    size_t n = sizeof(arr) / sizeof(arr[0]);
    int k = 10;
    
    long long result = find_max_sum_disjoint_pairs(arr, n, k);
    
    if (result == 0) {
        printf("No valid pair found\n");
    } else {
        printf("Maximum sum: %lld\n", result);
    }
    
    return 0;
}