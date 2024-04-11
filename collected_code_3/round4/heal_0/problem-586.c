#include <stdio.h>

void splitAdd(int arr[], int length, int position) {
    int temp[length];
    for(int i = 0; i < length; i++) {
        temp[(i + length - position) % length] = arr[i];
    }
    for(int i = 0; i < length; i++) {
        arr[i] = temp[i];
    }
}

int main() {
    int arr[] = {1, 2, 3, 4, 5, 6, 7};
    int length = sizeof(arr) / sizeof(arr[0]);
    int position = 2;

    splitAdd(arr, length, position);

    for(int i = 0; i < length; i++) {
        printf("%d ", arr[i]);
    }

    return 0;
}