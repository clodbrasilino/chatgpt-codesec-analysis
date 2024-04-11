#include <stdio.h>

void filter_odd(int arr[], int size) {
    for(int i = 0; i < size; i++) {
        if(arr[i] % 2 == 0) {
            printf("%d ", arr[i]);
        }
    }
    printf("\n");
}

int main() {
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int size = sizeof(arr) / sizeof(arr[0]);

    filter_odd(arr, size);

    return 0;
}