#include <stdio.h>
#include <stddef.h>

size_t remove_negatives(int *array, size_t size);

size_t remove_negatives(int *array, size_t size) {
    if (array == NULL || size == 0) {
        return 0;
    }

    size_t valid_index = 0;

    for (size_t i = 0; i < size; i++) {
        if (array[i] >= 0) {
            array[valid_index] = array[i];
            valid_index++;
        }
    }

    return valid_index;
}

int main(void) {
    int numbers[] = {10, -5, 3, -1, 0, -8, 7, 2, -4};
    size_t original_size = sizeof(numbers) / sizeof(numbers[0]);

    size_t new_size = remove_negatives(numbers, original_size);

    for (size_t i = 0; i < new_size; i++) {
        printf("%d", numbers[i]);
        if (i < new_size - 1) {
            printf(" ");
        }
    }
    printf("\n");

    return 0;
}