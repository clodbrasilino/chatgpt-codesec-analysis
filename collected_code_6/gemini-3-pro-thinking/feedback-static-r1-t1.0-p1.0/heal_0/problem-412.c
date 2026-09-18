#include <stdio.h>
#include <stddef.h>

void remove_odds(int *array, size_t *size) {
    if (array == NULL || size == NULL) {
        return;
    }

    size_t write_index = 0;
    
    for (size_t read_index = 0; read_index < *size; read_index++) {
        if (array[read_index] % 2 == 0) {
            array[write_index] = array[read_index];
            write_index++;
        }
    }
    
    *size = write_index;
}

int main(void) {
    int numbers[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, -3, -4, 0};
    size_t size = sizeof(numbers) / sizeof(numbers[0]);

    remove_odds(numbers, &size);

    for (size_t i = 0; i < size; i++) {
        printf("%d ", numbers[i]);
    }
    printf("\n");

    return 0;
}