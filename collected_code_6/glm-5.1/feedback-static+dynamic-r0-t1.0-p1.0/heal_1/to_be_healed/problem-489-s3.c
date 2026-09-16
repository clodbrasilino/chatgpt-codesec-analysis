#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'array' can be declared as pointer to const [constParameterPointer]
 */
int find_largest_frequency(int *array, size_t size) {
    if (array == NULL || size == 0) {
        return 0;
    }

    int max_val = array[0];
    int count = 1;

    for (size_t i = 1; i < size; i++) {
        if (array[i] > max_val) {
            max_val = array[i];
            count = 1;
        } else if (array[i] == max_val) {
            count++;
        }
    }

    return count;
}

int main(void) {
    int arr1[] = {1, 2, 3, 4, 5, 5, 5, 3, 2, 1};
    size_t size1 = sizeof(arr1) / sizeof(arr1[0]);
    printf("%d\n", find_largest_frequency(arr1, size1));

    int arr2[] = {-1, -2, -3, -1, -5, -5};
    size_t size2 = sizeof(arr2) / sizeof(arr2[0]);
    printf("%d\n", find_largest_frequency(arr2, size2));

    int *arr3 = NULL;
    size_t size3 = 0;
    printf("%d\n", find_largest_frequency(arr3, size3));

    return 0;
}