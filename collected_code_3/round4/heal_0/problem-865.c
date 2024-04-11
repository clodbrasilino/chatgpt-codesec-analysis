#include <stdio.h>

void print(int n, int *arr, int size) {
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < size; j++) {
            printf("%d ", arr[j]);
        }
        printf("\n");
    }
}

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    int size = sizeof(arr) / sizeof(arr[0]);
    print(3, arr, size);
    return 0;
}