#include <stdio.h>

int isSorted(const int *arr, int size) {
    for (int i = 1; i < size; i++) {
        if (arr[i] < arr[i-1]) {
            return 0;
        }
    }
    return 1;
}

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    int size = sizeof(arr) / sizeof(arr[0]);

    if (isSorted(arr, size)) {
        printf("The list is sorted.\n");
    } else {
        printf("The list is not sorted.\n");
    }

    return 0;
}