#include <stdio.h>
#include <stdbool.h>

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as const array [constParameter]
 */
bool isMajorityElement(int arr[], int n, int target) {
    if (arr == NULL || n <= 0) {
        return false;
    }

    int left = 0;
    int right = n - 1;
    int first_index = -1;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        if ((mid == 0 || target > arr[mid - 1]) && arr[mid] == target) {
            first_index = mid;
            break;
        } else if (target > arr[mid]) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    if (first_index == -1) {
        return false;
    }

    int last_index = first_index + n / 2;
    if (last_index < n && arr[last_index] == target) {
        return true;
    }

    return false;
}

int main() {
    int arr[] = {1, 2, 3, 3, 3, 3, 10};
    int n = sizeof(arr) / sizeof(arr[0]);
    int target = 3;

    if (isMajorityElement(arr, n, target)) {
        printf("Element is a majority element.\n");
    } else {
        printf("Element is not a majority element.\n");
    }

    return 0;
}