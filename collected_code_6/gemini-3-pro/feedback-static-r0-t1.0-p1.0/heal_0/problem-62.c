#include <stdio.h>
#include <stddef.h>

int find_smallest(const int *array, size_t size, int *smallest);

int find_smallest(const int *array, size_t size, int *smallest) {
    if (array == NULL || smallest == NULL || size == 0) {
        return -1;
    }

    *smallest = array[0];
    
    for (size_t i = 1; i < size; ++i) {
        if (array[i] < *smallest) {
            *smallest = array[i];
        }
    }

    return 0;
}

int main(void) {
    const int numbers[] = {89, 42, 17, 3, 105, -12, 4};
    size_t size = sizeof(numbers) / sizeof(numbers[0]);
    int smallest_value;

    if (find_smallest(numbers, size, &smallest_value) == 0) {
        printf("The smallest number is: %d\n", smallest_value);
    } else {
        printf("Error: Invalid input or empty list.\n");
        return 1;
    }

    return 0;
}