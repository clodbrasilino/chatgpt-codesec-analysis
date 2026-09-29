#include <stdio.h>

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as const array [constParameter]
 */
int binary_search_first_occurrence(int arr[], int size, int target) {
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
    int sorted_array[] = {1, 2, 2, 2, 3, 4, 5, 5, 6, 7};
    int size = sizeof(sorted_array) / sizeof(sorted_array[0]);
    int target = 2;
    
    int index = binary_search_first_occurrence(sorted_array, size, target);
    
    if (index != -1) {
        printf("First occurrence of %d is at index %d\n", target, index);
    } else {
        printf("%d not found in array\n", target);
    }
    
    return 0;
}