#include <stdio.h>
#include <stdlib.h>

int countEven(const int *arr, int size) {
    if (arr == NULL || size <= 0) {
        return 0;
    }
    int count = 0;
    for (int i = 0; i < size; ++i) {
        if (arr[i] % 2 == 0) {
            count++;
        }
    }
    return count;
}

int main() {
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int size = sizeof(arr) / sizeof(arr[0]);
    int evenCount = countEven(arr, size);
    printf("Number of even elements: %d\n", evenCount);
    return 0;
}