#include <stdio.h>

int first_position(int arr[], int n, int target) {
    int left = 0, right = n - 1;
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
    int arr[] = {1, 2, 2, 2, 3, 4, 5, 6, 6, 7};
    int n = sizeof(arr) / sizeof(arr[0]);
    int target = 2;
    int position = first_position(arr, n, target);

    if (position != -1) {
        printf("First position of %d is %d\n", target, position);
    } else {
        printf("%d not found in array\n", target);
    }

    return 0;
}