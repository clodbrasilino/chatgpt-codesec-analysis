#include <stdio.h>
#include <stdlib.h>

int findExtra(const int arr1[], const int arr2[], int n) {
    int low = 0, high = n - 2;
    int index = n - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (arr2[mid] == arr1[mid]) {
            low = mid + 1;
        } else {
            index = mid;
            high = mid - 1;
        }
    }

    return index;
}

int main(void) {
    int arr1[] = {2, 4, 6, 8, 10, 12, 13};
    int arr2[] = {2, 4, 6, 8, 10, 12};
    int n = sizeof(arr1) / sizeof(arr1[0]);

    int extraIndex = findExtra(arr1, arr2, n);

    printf("%d\n", extraIndex);

    return 0;
}