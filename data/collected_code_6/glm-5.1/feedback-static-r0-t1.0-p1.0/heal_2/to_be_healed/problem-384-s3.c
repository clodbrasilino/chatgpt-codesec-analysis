#include <stdio.h>
#include <stdlib.h>

int find_smallest_frequency(const int *array, size_t size) {
    if (array == NULL || size == 0) {
        return -1;
    }

    int smallest = array[0];
    int frequency = 1;

    for (size_t i = 1; i < size; i++) {
        if (array[i] < smallest) {
            smallest = array[i];
            frequency = 1;
        } else if (array[i] == smallest) {
            frequency++;
        }
    }

    return frequency;
}

int main(void) {
    int arr1[] = {5, 2, 8, 2, 7, 2, 3};
    size_t size1 = sizeof(arr1) / sizeof(arr1[0]);
    int result1 = find_smallest_frequency(arr1, size1);
    printf("%d\n", result1);

    int arr2[] = {10, 20, 30};
    size_t size2 = sizeof(arr2) / sizeof(arr2[0]);
    int result2 = find_smallest_frequency(arr2, size2);
    printf("%d\n", result2);

    /* Possible weaknesses found:
     *  Variable 'arr3' can be declared as pointer to const [constVariablePointer]
     */
    int *arr3 = NULL;
    size_t size3 = 0;
    int result3 = find_smallest_frequency(arr3, size3);
    printf("%d\n", result3);

    return 0;
}