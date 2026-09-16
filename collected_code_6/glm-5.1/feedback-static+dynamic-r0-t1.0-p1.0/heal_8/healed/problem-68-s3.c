#include <stdio.h>
#include <stdbool.h>

bool is_monotonic(const int *arr, size_t size) {
    if (size <= 1) {
        return true;
    }

    bool increasing = true;
    bool decreasing = true;

    for (size_t i = 0; i < size - 1; i++) {
        if (arr[i] > arr[i + 1]) {
            increasing = false;
        }
        if (arr[i] < arr[i + 1]) {
            decreasing = false;
        }
        
        if (!increasing && !decreasing) {
            return false;
        }
    }

    return true;
}

int main(void) {
    const int arr1[] = {1, 2, 2, 3};
    size_t size1 = sizeof(arr1) / sizeof(arr1[0]);

    const int arr2[] = {6, 5, 4, 4};
    size_t size2 = sizeof(arr2) / sizeof(arr2[0]);

    const int arr3[] = {1, 3, 2};
    size_t size3 = sizeof(arr3) / sizeof(arr3[0]);

    const int arr4[] = {5};
    size_t size4 = 1;

    printf("%s\n", is_monotonic(arr1, size1) ? "True" : "False");
    printf("%s\n", is_monotonic(arr2, size2) ? "True" : "False");
    printf("%s\n", is_monotonic(arr3, size3) ? "True" : "False");
    printf("%s\n", is_monotonic(arr4, size4) ? "True" : "False");

    return 0;
}