#include <stdio.h>

int findLastPosition(int arr[], int n, int target) {
    int start = 0, end = n - 1, ans = -1;
    while (start <= end) {
        int mid = (start + end) / 2;
        if (arr[mid] == target) {
            ans = mid;
            start = mid + 1;
        } else if (arr[mid] < target) {
            start = mid + 1;
        } else {
            end = mid - 1;
        }
    }
    return ans;
}

int main() {
    int arr[] = {1, 2, 3, 4, 4, 4, 5, 6, 7, 8, 9};
    int n = sizeof(arr) / sizeof(arr[0]);
    int target = 4;
    int index = findLastPosition(arr, n, target);
    if (index != -1) {
        printf("Last occurrence of %d is at index %d\n", target, index);
    } else {
        printf("%d not found in array\n", target);
    }
    return 0;
}