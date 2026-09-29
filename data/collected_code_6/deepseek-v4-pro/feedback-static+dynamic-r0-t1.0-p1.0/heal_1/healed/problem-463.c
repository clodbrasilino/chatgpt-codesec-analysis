#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

long long maxProductSubarray(int arr[], int n, int *start, int *end) {
    if (n <= 0 || arr == NULL) return 0;
    
    long long max_product = arr[0];
    long long min_product = arr[0];
    long long global_max = arr[0];
    int current_start = 0;
    int max_start = 0;
    int max_end = 0;
    
    for (int i = 1; i < n; i++) {
        if (arr[i] < 0) {
            long long temp = max_product;
            max_product = min_product;
            min_product = temp;
        }
        
        long long candidate1 = max_product * arr[i];
        long long candidate2 = arr[i];
        
        if (candidate2 > candidate1) {
            max_product = candidate2;
            current_start = i;
        } else {
            max_product = candidate1;
        }
        
        long long min_candidate1 = min_product * arr[i];
        long long min_candidate2 = arr[i];
        
        min_product = (min_candidate2 < min_candidate1) ? min_candidate2 : min_candidate1;
        
        if (max_product > global_max) {
            global_max = max_product;
            max_start = current_start;
            max_end = i;
        }
    }
    
    *start = max_start;
    *end = max_end;
    return global_max;
}

int main(void) {
    int n;
    printf("Enter the size of array: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid input\n");
        return 1;
    }
    
    int *arr = (int *)malloc((size_t)n * sizeof(int));
    if (arr == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }
    
    printf("Enter %d elements: ", n);
    for (int i = 0; i < n; i++) {
        if (scanf("%d", &arr[i]) != 1) {
            printf("Invalid input\n");
            free(arr);
            return 1;
        }
    }
    
    int start = 0, end = 0;
    long long result = maxProductSubarray(arr, n, &start, &end);
    
    printf("Maximum product subarray: ");
    for (int i = start; i <= end; i++) {
        printf("%d", arr[i]);
        if (i < end) printf(" ");
    }
    printf("\nMaximum product: %lld\n", result);
    
    free(arr);
    return 0;
}