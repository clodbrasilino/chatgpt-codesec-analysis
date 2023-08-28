#include <stdio.h>

void iteratePairs(int arr[], int size) {
    for(int i = 0; i < size-1; i++) {
        printf("(%d, %d)\n", arr[i], arr[i+1]);
    }
}

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    int size = sizeof(arr) / sizeof(arr[0]);
    iteratePairs(arr, size);

    return 0;
}