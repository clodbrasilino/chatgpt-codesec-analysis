#include <stdio.h>

int findMaxLength(const int arr[], int size) {
    int maxLength = 0;
    int currentLength = 0;

    for (int i = 0; i < size; i++) {
        if (arr[i] != 0) {
            currentLength++;
        } else {
            if (currentLength > maxLength) {
                maxLength = currentLength;
            }
            currentLength = 0;
        }
    }

    if (currentLength > maxLength) {
        maxLength = currentLength;
    }

    return maxLength;
}

int main() {
    int arr[] = {1, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0, 0, 1};
    int size = sizeof(arr) / sizeof(arr[0]);

    int maxLength = findMaxLength(arr, size);

    printf("The list with maximum length is: %d\n", maxLength);

    return 0;
}