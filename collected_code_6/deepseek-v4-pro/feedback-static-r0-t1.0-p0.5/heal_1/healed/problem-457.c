#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    int length;
    int start_index;
} Sublist;

Sublist find_minimum_length_sublist(const int *arr, int n, int target_sum) {
    Sublist result;
    result.data = NULL;
    result.length = 0;
    result.start_index = -1;
    
    if (arr == NULL || n <= 0) {
        return result;
    }
    
    int min_length = n + 1;
    int current_sum = 0;
    int left = 0;
    
    for (int right = 0; right < n; right++) {
        current_sum += arr[right];
        
        while (current_sum >= target_sum && left <= right) {
            int current_length = right - left + 1;
            if (current_length < min_length) {
                min_length = current_length;
                result.start_index = left;
                result.length = current_length;
            }
            current_sum -= arr[left];
            left++;
        }
    }
    
    if (result.start_index != -1) {
        result.data = (int *)malloc(result.length * sizeof(int));
        if (result.data == NULL) {
            result.length = 0;
            result.start_index = -1;
            return result;
        }
        for (int i = 0; i < result.length; i++) {
            result.data[i] = arr[result.start_index + i];
        }
    }
    
    return result;
}

int main(void) {
    int arr[] = {2, 3, 1, 2, 4, 3};
    int n = sizeof(arr) / sizeof(arr[0]);
    int target = 7;
    
    Sublist result = find_minimum_length_sublist(arr, n, target);
    
    if (result.data != NULL) {
        printf("Minimum length sublist: ");
        for (int i = 0; i < result.length; i++) {
            printf("%d ", result.data[i]);
        }
        printf("\n");
        printf("Length: %d\n", result.length);
        printf("Start index: %d\n", result.start_index);
        free(result.data);
    } else {
        printf("No sublist found\n");
    }
    
    return 0;
}