#include <stdio.h>

int findDuplicate(const int arr[], int size) {
    int i, j;
    for (i = 0; i < size; i++) {
        for (j = i + 1; j < size; j++) {
            if (arr[i] == arr[j]) {
                return arr[i];
            }
        }
    }
    return -1;
}

int main() {
    int arr[] = {4, 7, 2, 6, 2, 7, 9};
    int size = sizeof(arr) / sizeof(arr[0]);
    int duplicate = findDuplicate(arr, size);

    if (duplicate != -1) {
        printf("First duplicate element: %d\n", duplicate);
    } else {
        printf("No duplicate elements found.\n");
    }
    return 0;
}