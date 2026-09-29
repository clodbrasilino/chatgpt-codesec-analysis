#include <stdio.h>
#include <stdlib.h>

void printDuplicates(int* arr, int size) {
    int i, j;
    for(i = 0; i < size; i++) {
        for(j = i + 1; j < size; j++) {
            if(arr[i] == arr[j]) {
                printf("%d ", arr[i]);
                break;
            }
        }
    }
}

int main() {
    int arr[] = {1, 2, 3, 2, 4, 5, 6, 4, 7, 8, 9, 10, 10};
    int size = sizeof(arr) / sizeof(arr[0]);
    printDuplicates(arr, size);
    return 0;
}