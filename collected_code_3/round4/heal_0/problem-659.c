#include <stdio.h>
#include <stdlib.h>

void printDuplicates(int arr[], int size) {
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
    int arr[] = {10, 20, 30, 20, 40, 10, 50, 60, 30};
    int size = sizeof(arr) / sizeof(arr[0]);
    printDuplicates(arr, size);
    return 0;
}