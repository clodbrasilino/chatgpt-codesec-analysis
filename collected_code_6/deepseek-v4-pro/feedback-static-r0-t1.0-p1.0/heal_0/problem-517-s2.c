#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int find_largest_positive(int *arr, size_t size) {
    int largest = -1;
    for (size_t i = 0; i < size; i++) {
        if (arr[i] > 0 && arr[i] > largest) {
            largest = arr[i];
        }
    }
    return largest;
}

int main(void) {
    int numbers[] = {5, -2, 10, 0, 3, -8, 7};
    size_t count = sizeof(numbers) / sizeof(numbers[0]);
    int result = find_largest_positive(numbers, count);

    if (result != -1) {
        printf("Largest positive number: %d\n", result);
    } else {
        printf("No positive number found\n");
    }

    return 0;
}