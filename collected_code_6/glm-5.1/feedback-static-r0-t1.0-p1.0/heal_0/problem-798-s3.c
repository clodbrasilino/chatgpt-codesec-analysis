#include <stdio.h>
#include <stdlib.h>

int sum_array(const int *array, size_t size) {
    if (array == NULL || size == 0) {
        return 0;
    }

    int sum = 0;
    for (size_t i = 0; i < size; ++i) {
        sum += array[i];
    }

    return sum;
}

int main(void) {
    size_t size = 5;
    int *array = (int *)malloc(size * sizeof(int));
    
    if (array == NULL) {
        return EXIT_FAILURE;
    }

    array[0] = 1;
    array[1] = 2;
    array[2] = 3;
    array[3] = 4;
    array[4] = 5;

    int total = sum_array(array, size);
    printf("%d\n", total);

    free(array);
    array = NULL;

    return EXIT_SUCCESS;
}