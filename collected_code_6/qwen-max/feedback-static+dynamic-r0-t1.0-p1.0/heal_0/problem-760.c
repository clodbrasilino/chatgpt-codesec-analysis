#include <stdbool.h>
#include <stdio.h>

bool is_single_distinct_element(int *arr, size_t size) {
    if (size < 2) {
        return true;
    }

    int first_element = arr[0];
    for (size_t i = 1; i < size; ++i) {
        if (arr[i] != first_element) {
            return false;
        }
    }
    return true;
}

int main() {
    int arr1[] = {1, 1, 1, 1};
    size_t size1 = sizeof(arr1) / sizeof(arr1[0]);
    
    int arr2[] = {1, 2, 1, 1};
    size_t size2 = sizeof(arr2) / sizeof(arr2[0]);

    printf("%s\n", is_single_distinct_element(arr1, size1) ? "True" : "False");
    printf("%s\n", is_single_distinct_element(arr2, size2) ? "True" : "False");

    return 0;
}