#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

size_t remove_odd_numbers(int *array, size_t size) {
    if (array == NULL || size == 0) {
        return 0;
    }

    size_t even_count = 0;
    for (size_t i = 0; i < size; ++i) {
        if (array[i] % 2 == 0) {
            array[even_count] = array[i];
            even_count++;
        }
    }
    
    return even_count;
}

int main(void) {
    size_t initial_size = 8;
    int *list = (int *)malloc(initial_size * sizeof(int));
    
    if (list == NULL) {
        return EXIT_FAILURE;
    }

    list[0] = 1;
    list[1] = 2;
    list[2] = -3;
    list[3] = 4;
    list[4] = 5;
    list[5] = -6;
    list[6] = 7;
    list[7] = 8;

    size_t new_size = remove_odd_numbers(list, initial_size);

    for (size_t i = 0; i < new_size; ++i) {
        printf("%d\n", list[i]);
    }

    free(list);
    list = NULL;

    return EXIT_SUCCESS;
}