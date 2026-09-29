#include <stdio.h>
#include <stdlib.h>

size_t get_frequency(const int *array, size_t size, int target) {
    if (array == NULL) {
        return 0;
    }

    size_t count = 0;
    for (size_t i = 0; i < size; i++) {
        if (array[i] == target) {
            count++;
        }
    }
    return count;
}

int main(void) {
    int my_array[] = {1, 2, 3, 2, 4, 2, 5};
    size_t size = sizeof(my_array) / sizeof(my_array[0]);
    int target = 2;

    size_t frequency = get_frequency(my_array, size, target);

    printf("The frequency of %d is: %zu\n", target, frequency);

    return EXIT_SUCCESS;
}