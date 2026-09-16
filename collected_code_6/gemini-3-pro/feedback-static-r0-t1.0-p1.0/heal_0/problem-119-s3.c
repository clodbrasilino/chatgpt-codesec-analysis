#include <stdio.h>
#include <stdlib.h>

int findSingleElement(const int* arr, int size) {
    if (arr == NULL || size <= 0 || size % 2 == 0) {
        return -1; 
    }

    int left = 0;
    int right = size - 1;

    while (left < right) {
        int mid = left + (right - left) / 2;

        if (mid % 2 == 1) {
            mid--;
        }

        if (arr[mid] == arr[mid + 1]) {
            left = mid + 2;
        } else {
            right = mid;
        }
    }

    return arr[left];
}

int main(void) {
    int arr[] = {1, 1, 2, 2, 3, 4, 4, 5, 5};
    int size = sizeof(arr) / sizeof(arr[0]);

    int result = findSingleElement(arr, size);

    if (result != -1) {
        printf("%d\n", result);
    } else {
        printf("Invalid input or no single element found.\n");
    }

    return 0;
}