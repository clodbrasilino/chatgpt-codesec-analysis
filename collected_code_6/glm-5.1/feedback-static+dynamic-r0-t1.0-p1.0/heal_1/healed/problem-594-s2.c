#include <stdio.h>

int find_difference(const int *list, size_t size) {
    if (list == NULL || size == 0) {
        return 0;
    }

    int first_even = 0;
    int first_odd = 0;
    int even_found = 0;
    int odd_found = 0;

    for (size_t i = 0; i < size; i++) {
        if (list[i] % 2 == 0 && !even_found) {
            first_even = list[i];
            even_found = 1;
        } else if (list[i] % 2 != 0 && !odd_found) {
            first_odd = list[i];
            odd_found = 1;
        }

        if (even_found && odd_found) {
            break;
        }
    }

    int result = 0;

    if (even_found && odd_found) {
        result = first_even - first_odd;
    } else if (even_found) {
        result = first_even;
    } else if (odd_found) {
        result = -first_odd;
    }

    return result;
}

int main(void) {
    int arr1[] = {1, 2, 3, 4, 5};
    size_t size1 = sizeof(arr1) / sizeof(arr1[0]);
    printf("%d\n", find_difference(arr1, size1));

    int arr2[] = {2, 4, 6, 8};
    size_t size2 = sizeof(arr2) / sizeof(arr2[0]);
    printf("%d\n", find_difference(arr2, size2));

    int arr3[] = {1, 3, 5, 7};
    size_t size3 = sizeof(arr3) / sizeof(arr3[0]);
    printf("%d\n", find_difference(arr3, size3));

    return 0;
}