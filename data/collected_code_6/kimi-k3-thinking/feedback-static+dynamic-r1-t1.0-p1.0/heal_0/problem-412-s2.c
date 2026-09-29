#include <stdio.h>
#include <stdlib.h>

size_t remove_odd_numbers(int *array, size_t size)
{
    size_t i;
    size_t write_index = 0;

    if (array == NULL) {
        return 0;
    }

    for (i = 0; i < size; i++) {
        if (array[i] % 2 == 0) {
            array[write_index] = array[i];
            write_index++;
        }
    }

    return write_index;
}

int main(void)
{
    size_t size = 10;
    size_t new_size;
    size_t i;
    int *numbers = malloc(size * sizeof(int));

    if (numbers == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    numbers[0] = 1;
    numbers[1] = 2;
    numbers[2] = 3;
    numbers[3] = 4;
    numbers[4] = 5;
    numbers[5] = 6;
    numbers[6] = 7;
    numbers[7] = 8;
    numbers[8] = 9;
    numbers[9] = 10;

    printf("Original list: ");
    for (i = 0; i < size; i++) {
        printf("%d ", numbers[i]);
    }
    printf("\n");

    new_size = remove_odd_numbers(numbers, size);

    printf("List after removing odd numbers: ");
    for (i = 0; i < new_size; i++) {
        printf("%d ", numbers[i]);
    }
    printf("\n");

    free(numbers);
    numbers = NULL;

    return EXIT_SUCCESS;
}