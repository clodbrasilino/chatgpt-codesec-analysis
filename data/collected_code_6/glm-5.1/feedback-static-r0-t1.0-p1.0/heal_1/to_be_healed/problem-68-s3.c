#include <stdio.h>
#include <stdbool.h>

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as pointer to const [constParameterPointer]
 */
bool is_monotonic(int *arr, size_t size) {
    if (size <= 2) {
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
    }

    return increasing || decreasing;
}

int main(void) {
    int arr1[] = {1, 2, 2, 3};
    size_t size1 = sizeof(arr1) / sizeof(arr1[0]);

    int arr2[] = {6, 5, 4, 4};
    size_t size2 = sizeof(arr2) / sizeof(arr2[0]);

    int arr3[] = {1, 3, 2};
    size_t size3 = sizeof(arr3) / sizeof(arr3[0]);

    int arr4[] = {5};
    size_t size4 = sizeof(arr4) / sizeof(arr4[0]);

    printf("%d\n", is_monotonic(arr1, size1));
    printf("%d\n", is_monotonic(arr2, size2));
    printf("%d\n", is_monotonic(arr3, size3));
    printf("%d\n", is_monotonic(arr4, size4));

    return 0;
}