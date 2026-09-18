#include <stdio.h>

size_t count_elements(int* array, size_t array_size, int lower_bound, int upper_bound) {
    size_t counter = 0;

    if(array == NULL || array_size == 0) {
        printf("The given array is either NULL or the size is zero.\n");
        return counter;
    }

    for (size_t i = 0; i < array_size; ++i) {
        if (array[i] >= lower_bound && array[i] <= upper_bound) {
            ++counter;
        }
    }

    return counter;
}

int main() {
    int array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    size_t array_size = sizeof(array) / sizeof(array[0]);
    int lower_bound = 2;
    int upper_bound = 8;

    size_t count = count_elements(array, array_size, lower_bound, upper_bound);

    printf("The number of elements between the range %d and %d is: %zu\n",
           lower_bound, upper_bound, count);

    return 0;
}