#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as pointer to const [constParameterPointer]
 */
int find_largest_frequency(int *arr, size_t size) {
    if (size == 0 || arr == NULL) {
        return 0;
    }

    int max_val = arr[0];
    int count = 1;

    for (size_t i = 1; i < size; i++) {
        if (arr[i] > max_val) {
            max_val = arr[i];
            count = 1;
        } else if (arr[i] == max_val) {
            count++;
        }
    }

    return count;
}

int main(void) {
    int arr1[] = {1, 2, 3, 4, 5, 5, 5};
    size_t size1 = sizeof(arr1) / sizeof(arr1[0]);
    printf("%d\n", find_largest_frequency(arr1, size1));

    int arr2[] = {7, 7, 7, 7, 7};
    size_t size2 = sizeof(arr2) / sizeof(arr2[0]);
    printf("%d\n", find_largest_frequency(arr2, size2));

    int arr3[] = {-1, -2, -3, -1, -1};
    size_t size3 = sizeof(arr3) / sizeof(arr3[0]);
    printf("%d\n", find_largest_frequency(arr3, size3));

    size_t size4 = 0;
    printf("%d\n", find_largest_frequency(NULL, size4));

    return 0;
}