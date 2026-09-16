#include <stdio.h>
#include <stdbool.h>

bool canBeSorted(const int arr[], int n) {
    if (arr == NULL || n <= 0) {
        return false;
    }

    int left = 0;
    int right = n - 1;
    int current_min = -2147483648; 

    while (left <= right) {
        if (arr[left] < arr[right]) {
            if (arr[left] < current_min) {
                return false;
            }
            current_min = arr[left];
            left++;
        } else {
            if (arr[right] < current_min) {
                return false;
            }
            current_min = arr[right];
            right--;
        }
    }

    return true;
}

int main(void) {
    int arr1[] = {1, 3, 5, 4, 2};
    int n1 = sizeof(arr1) / sizeof(arr1[0]);
    if (canBeSorted(arr1, n1)) {
        printf("Array 1 can be sorted.\n");
    } else {
        printf("Array 1 cannot be sorted.\n");
    }

    int arr2[] = {5, 3, 1, 2, 4};
    int n2 = sizeof(arr2) / sizeof(arr2[0]);
    if (canBeSorted(arr2, n2)) {
        printf("Array 2 can be sorted.\n");
    } else {
        printf("Array 2 cannot be sorted.\n");
    }

    return 0;
}