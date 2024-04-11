#include <stdio.h>
#include <stdlib.h>

void getNLargest(int* arr, int arr_size, int n) {
    int i, j, temp;
    for (i = 0; i < arr_size; i++) {
        for (j = i + 1; j < arr_size; j++) {
            if (arr[i] < arr[j]) {
                temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
    printf("The %d largest elements are: ", n);
    for (i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
}

int main() {
    int arr[] = {12, 34, 7, 2, 5, 78, 23, 56, 89};
    int n = 3;
    int arr_size = sizeof(arr) / sizeof(arr[0]);
    getNLargest(arr, arr_size, n);
    return 0;
}