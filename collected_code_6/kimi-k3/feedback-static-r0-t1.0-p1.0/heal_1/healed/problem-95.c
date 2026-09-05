#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int find_min_sublist_length(const int *arr, int size, int target_sum) {
    if (arr == NULL || size <= 0) {
        return 0;
    }
    
    int min_length = INT_MAX;
    int current_sum = 0;
    int start = 0;
    int found = 0;
    
    for (int end = 0; end < size; end++) {
        current_sum += arr[end];
        
        while (current_sum >= target_sum && start <= end) {
            found = 1;
            int current_length = end - start + 1;
            if (current_length < min_length) {
                min_length = current_length;
            }
            current_sum -= arr[start];
            start++;
        }
    }
    
    if (!found) {
        return 0;
    }
    
    return min_length;
}

int main(void) {
    int size;
    int target_sum;
    int result;
    int *arr = NULL;
    
    printf("Enter the size of array: ");
    if (scanf("%d", &size) != 1 || size <= 0) {
        fprintf(stderr, "Invalid input for array size\n");
        return EXIT_FAILURE;
    }
    
    arr = (int *)malloc(size * sizeof(int));
    if (arr == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }
    
    printf("Enter %d elements: ", size);
    for (int i = 0; i < size; i++) {
        if (scanf("%d", &arr[i]) != 1) {
            fprintf(stderr, "Invalid input for array element\n");
            free(arr);
            arr = NULL;
            return EXIT_FAILURE;
        }
    }
    
    printf("Enter target sum: ");
    if (scanf("%d", &target_sum) != 1) {
        fprintf(stderr, "Invalid input for target sum\n");
        free(arr);
        arr = NULL;
        return EXIT_FAILURE;
    }
    
    result = find_min_sublist_length(arr, size, target_sum);
    
    if (result == 0) {
        printf("No sublist found with sum >= %d\n", target_sum);
    } else {
        printf("Minimum length of sublist: %d\n", result);
    }
    
    free(arr);
    arr = NULL;
    
    return EXIT_SUCCESS;
}