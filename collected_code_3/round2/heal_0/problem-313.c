#include <stdio.h>

void print_positive_numbers(int *arr, int size) {
    for(int i = 0; i < size; i++) {
        if(arr[i] > 0) {
            printf("%d ", arr[i]);
        }
    }
    printf("\n");
}

int main() {
    int arr[] = {-1, 2, -3, 4, -5, 6};
    int size = sizeof(arr) / sizeof(arr[0]);

    print_positive_numbers(arr, size);

    return 0;
}