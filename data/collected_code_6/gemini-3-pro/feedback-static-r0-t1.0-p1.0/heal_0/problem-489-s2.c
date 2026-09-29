#include <stdio.h>
#include <stdlib.h>

int find_frequency_of_largest(const int *array, size_t size) {
    if (array == NULL || size == 0) {
        return 0;
    }

    int max_value = array[0];
    int frequency = 1;

    for (size_t i = 1; i < size; ++i) {
        if (array[i] > max_value) {
            max_value = array[i];
            frequency = 1;
        } else if (array[i] == max_value) {
            frequency++;
        }
    }

    return frequency;
}

int main(void) {
    int array[] = {3, 5, 2, 8, 8, 1, 8, 4};
    size_t size = sizeof(array) / sizeof(array[0]);

    int frequency = find_frequency_of_largest(array, size);
    
    printf("%d\n", frequency);

    return 0;
}