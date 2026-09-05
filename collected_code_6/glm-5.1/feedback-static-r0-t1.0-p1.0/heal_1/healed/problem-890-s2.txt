#include <stdio.h>
#include <stdlib.h>

int find_extra_element_index(const int *arr1, const int *arr2, int n) {
    int low = 0;
    int high = n - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (mid < n - 1 && arr1[mid] == arr2[mid]) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    return low;
}

int main() {
    int arr1[] = {2, 4, 6, 8, 10, 12, 13};
    int arr2[] = {2, 4, 6, 8, 10, 12};
    int n = sizeof(arr1) / sizeof(arr1[0]);

    if (n <= 0 || arr1 == NULL || arr2 == NULL) {
        return EXIT_FAILURE;
    }

    int index = find_extra_element_index(arr1, arr2, n);
    printf("%d\n", index);

    return EXIT_SUCCESS;
}