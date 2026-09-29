#include <stdio.h>
#include <stdbool.h>

bool canSortByCorners(int arr[], int n) {
    if (n == 0 || n == 1) return true;

    int l = 0, r = n - 1;
    int maxL = arr[0], minR = arr[n - 1];

    while (l < r) {
        if (arr[l] >= maxL && arr[r] <= minR) {
            maxL = arr[l];
            minR = arr[r];
            l++;
            r--;
        } else {
            return false;
        }
    }

    if (l == r && arr[l] > maxL && arr[l] < minR) {
        return false;
    }

    return true;
}

int main() {
    int arr1[] = {5, 3, 4, 2, 1};
    int arr2[] = {1, 3, 5, 4, 2};
    int arr3[] = {1, 2, 3, 4, 5};
    int arr4[] = {1, 5, 2, 4, 3};

    printf("Can sort by corners: %s\n", canSortByCorners(arr1, 5) ? "Yes" : "No");
    printf("Can sort by corners: %s\n", canSortByCorners(arr2, 5) ? "Yes" : "No");
    printf("Can sort by corners: %s\n", canSortByCorners(arr3, 5) ? "Yes" : "No");
    printf("Can sort by corners: %s\n", canSortByCorners(arr4, 5) ? "Yes" : "No");

    return 0;
}