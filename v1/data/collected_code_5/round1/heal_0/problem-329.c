#include <stdio.h>

int count_negatives(int *arr, int size) {
    int i, count = 0;
    
    if(arr == NULL || size < 1) {
        return 0;
    }

    for(i = 0; i < size; i++) {
        if(arr[i] < 0) {
            count++;
        }
    }

    return count;
}

int main() {
    int arr[] = {-1, 2, -3, 4, -5, 6, -7};
    int size = sizeof(arr)/sizeof(arr[0]);
    int count = count_negatives(arr, size);

    printf("Count of negative numbers: %d\n", count);

    return 0;
}