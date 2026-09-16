#include <stdio.h>
#include <stdlib.h>

int find_sum(const int *array, size_t size) {
    int sum = 0;
    for (size_t i = 0; i < size; i++) {
        sum += array[i];
    }
    return sum;
}

int main(void) {
    size_t size = 0;
    
    if (scanf("%zu", &size) != 1) {
        return EXIT_FAILURE;
    }

    if (size == 0) {
        printf("0\n");
        return EXIT_SUCCESS;
    }

    int *array = (int *)malloc(size * sizeof(int));
    if (array == NULL) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < size; i++) {
        if (scanf("%d", &array[i]) != 1) {
            free(array);
            return EXIT_FAILURE;
        }
    }

    int sum = find_sum(array, size);
    printf("%d\n", sum);

    free(array);
    return EXIT_SUCCESS;
}