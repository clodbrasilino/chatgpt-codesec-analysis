#include <stdio.h>

int find_last_position(int arr[], int size, int target) {
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
    int arr[] = {1, 2, 3, 3, 3, 4, 5, 6, 7};
    int size = sizeof(arr) / sizeof(arr[0]);
    int target = 3;
    
    int last_pos = find_last_position(arr, size, target);
    
    if (last_pos != -1) {
        printf("Last position of %d is %d\n", target, last_pos);
    } else {
        printf("%d not found in array\n", target);
    }
    
    return 0;
}