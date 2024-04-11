#include <stdio.h>

int findFirstPosition(int arr[], int n, int target) {
    int start = 0, end = n - 1;

    while (start <= end) {
        int mid = start + (end - start) / 2;

        if (arr[mid] == target) {
            if (mid == 0 || arr[mid - 1] != target) {
                return mid;
            }
            end = mid - 1;
        } else if (arr[mid] < target) {
            start = mid + 1;
        } else {
            end = mid - 1;
        }
    }

    return -1;
}

int main() {
    int arr[] = {1, 2, 3, 3, 3, 4, 5, 6, 7};
    int n = sizeof(arr) / sizeof(arr[0]);
    int target = 3;

    int position = findFirstPosition(arr, n, target);

    if (position != -1) {
        printf("First position of %d is %d\n", target, position);
    } else {
        printf("%d is not in the array\n", target);
    }

    return 0;
}