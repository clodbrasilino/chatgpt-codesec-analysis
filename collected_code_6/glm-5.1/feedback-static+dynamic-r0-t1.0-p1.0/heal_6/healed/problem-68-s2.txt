#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool is_monotonic(const int *arr, size_t size) {
    if (size <= 1) {
        return true;
    }

    bool increasing = false;
    bool decreasing = false;

    for (size_t i = 0; i < size - 1; i++) {
        if (arr[i] > arr[i + 1]) {
            decreasing = true;
        } else if (arr[i] < arr[i + 1]) {
            increasing = true;
        }

        if (increasing && decreasing) {
            return false;
        }
    }

    return true;
}

void print_bool(bool val) {
    printf("%s\n", val ? "True" : "False");
}

int main(void) {
    int arr1[] = {1, 2, 2, 3};
    size_t size1 = sizeof(arr1) / sizeof(arr1[0]);
    print_bool(is_monotonic(arr1, size1));
    
    int arr2[] = {6, 5, 4, 4};
    size_t size2 = sizeof(arr2) / sizeof(arr2[0]);
    print_bool(is_monotonic(arr2, size2));
    
    int arr3[] = {1, 3, 2};
    size_t size3 = sizeof(arr3) / sizeof(arr3[0]);
    print_bool(is_monotonic(arr3, size3));
    
    int arr4[] = {5};
    if (sizeof(arr4) / sizeof(arr4[0]) > 1) {
        size_t size4 = sizeof(arr4) / sizeof(arr4[0]);
        print_bool(is_monotonic(arr4, size4));
    } else {
        print_bool(true);
    }

    return 0;
}