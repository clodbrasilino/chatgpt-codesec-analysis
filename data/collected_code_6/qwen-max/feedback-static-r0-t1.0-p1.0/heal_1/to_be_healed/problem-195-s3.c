#include <stdio.h>

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as pointer to const [constParameterPointer]
 */
int find_first_position(int *arr, int size, int target) {
    int left = 0;
    int right = size - 1;
    int result = -1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == target) {
            result = mid;
            right = mid - 1; // Continue searching to the left
        } else if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return result;
}

int main() {
    int arr[] = {1, 2, 4, 4, 5, 6, 7};
    int size = sizeof(arr) / sizeof(arr[0]);
    int target = 4;
    int position = find_first_position(arr, size, target);
    if (position != -1) {
        printf("First occurrence of %d is at index: %d\n", target, position);
    } else {
        printf("%d not found in the array.\n", target);
    }
    return 0;
}