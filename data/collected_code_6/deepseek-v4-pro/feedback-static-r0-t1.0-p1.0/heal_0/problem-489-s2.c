#include <stdio.h>
#include <stdlib.h>

int frequency_of_largest(int *arr, int size) {
    if (arr == NULL || size <= 0) {
        return 0;
    }

    int largest = arr[0];
    int frequency = 1;

    for (int i = 1; i < size; i++) {
        if (arr[i] > largest) {
            largest = arr[i];
            frequency = 1;
        } else if (arr[i] == largest) {
            frequency++;
        }
    }

    return frequency;
}

int main(void) {
    int arr[] = {3, 5, 2, 5, 5, 7, 7, 7};
    int size = sizeof(arr) / sizeof(arr[0]);

    int result = frequency_of_largest(arr, size);
    printf("Frequency of largest value: %d\n", result);

    int empty_arr[] = {};
    int empty_size = 0;
    printf("Empty array result: %d\n", frequency_of_largest(empty_arr, empty_size));

    return 0;
}