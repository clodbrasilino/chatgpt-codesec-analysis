#include <stdio.h>

void splitAdd(int arr[], int length, int position) {
    int temp[position];
    for(int i = 0; i < position; i++) {
        temp[i] = arr[i];
    }
    for(int i = position; i < length; i++) {
        arr[i - position] = arr[i];
    }
    for(int i = 0; i < position; i++) {
        arr[length - position + i] = temp[i];
    }
}

int main() {
    int arr[] = {1, 2, 3, 4, 5, 6, 7};
    int length = sizeof(arr)/sizeof(arr[0]);
    int position = 2;
    splitAdd(arr, length, position);
    for(int i = 0; i < length; i++) {
        printf("%d ", arr[i]);
    }
    return 0;
}