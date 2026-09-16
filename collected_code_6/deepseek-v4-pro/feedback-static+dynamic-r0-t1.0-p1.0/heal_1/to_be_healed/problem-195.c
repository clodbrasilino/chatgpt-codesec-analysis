#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as const array [constParameter]
 */
int first_position(int arr[], int size, int target) {
    if (arr == NULL || size <= 0) {
        return -1;
    }
    
    int left = 0;
    int right = size - 1;
    int result = -1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (arr[mid] == target) {
            result = mid;
            right = mid - 1;
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
    
    int result = first_position(arr, size, target);
    
    if (result != -1) {
        printf("First position of %d is %d\n", target, result);
    } else {
        printf("%d not found in array\n", target);
    }
    
    return 0;
}