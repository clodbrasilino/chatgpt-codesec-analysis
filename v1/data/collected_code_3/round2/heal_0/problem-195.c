#include <stdio.h>

int findFirstPosition(int arr[], int n, int x) {
    int low = 0, high = n - 1, result = -1;
    while (low <= high) {
        int mid = (low + high) / 2;
        if (x == arr[mid]) {
            result = mid;
            high = mid - 1;
        }
        else if (x < arr[mid]) high = mid - 1;
        else low = mid + 1;
    }
    return result;
}

int main() {
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int n = sizeof(arr) / sizeof(arr[0]);
    int x = 5;
    int index = findFirstPosition(arr, n, x);
    if (index != -1) printf("Element %d found at index %d\n", x, index);
    else printf("Element %d not found in the array\n", x);
    return 0;
}