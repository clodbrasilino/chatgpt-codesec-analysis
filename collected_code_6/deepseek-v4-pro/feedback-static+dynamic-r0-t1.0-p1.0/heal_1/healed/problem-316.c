#include <stdio.h>

int find_last_occurrence(const int arr[], int size, int target) {
    int left = 0;
    int right = size - 1;
    int result = -1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (arr[mid] == target) {
            result = mid;
            left = mid + 1;
        } else if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    
    return result;
}

int main(void) {
    int arr[] = {1, 2, 2, 2, 3, 4, 5, 5, 6};
    int size = sizeof(arr) / sizeof(arr[0]);
    int target = 2;
    
    int index = find_last_occurrence(arr, size, target);
    
    if (index != -1) {
        printf("Last occurrence of %d is at index %d\n", target, index);
    } else {
        printf("%d not found in the array\n", target);
    }
    
    return 0;
}