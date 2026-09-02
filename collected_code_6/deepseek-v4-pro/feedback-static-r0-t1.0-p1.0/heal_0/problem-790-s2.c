#include <stdio.h>
#include <stdbool.h>

bool check_even_indices_even(const int arr[], size_t size) {
    for (size_t i = 0; i < size; i += 2) {
        if (arr[i] % 2 != 0) {
            return false;
        }
    }
    return true;
}

int main(void) {
    int arr1[] = {2, 1, 4, 3, 6, 5};
    size_t size1 = sizeof(arr1) / sizeof(arr1[0]);
    printf("%s\n", check_even_indices_even(arr1, size1) ? "true" : "false");

    int arr2[] = {2, 1, 3, 3, 6, 5};
    size_t size2 = sizeof(arr2) / sizeof(arr2[0]);
    printf("%s\n", check_even_indices_even(arr2, size2) ? "true" : "false");

    int arr3[] = {0, 1, 2, 3, 4, 5};
    size_t size3 = sizeof(arr3) / sizeof(arr3[0]);
    printf("%s\n", check_even_indices_even(arr3, size3) ? "true" : "false");

    return 0;
}