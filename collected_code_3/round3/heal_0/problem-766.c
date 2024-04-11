#include <stdio.h>

void iterate_pairs(int* arr, int size) {
    for(int i = 0; i < size - 1; i++) {
        printf("Pair: %d, %d\n", arr[i], arr[i+1]);
    }
}

int main() {
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int size = sizeof(arr) / sizeof(arr[0]);

    iterate_pairs(arr, size);

    return 0;
}