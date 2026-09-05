#include <stdio.h>
#include <stdlib.h>

void find_cubes(const int *input, int *output, size_t size) {
    if (input == NULL || output == NULL || size == 0) {
        return;
    }
    for (size_t i = 0; i < size; i++) {
        output[i] = input[i] * input[i] * input[i];
    }
}

int main(void) {
    size_t size = 5;
    int *input = malloc(size * sizeof(int));
    if (input == NULL) {
        return 1;
    }
    
    int *output = malloc(size * sizeof(int));
    if (output == NULL) {
        free(input);
        return 1;
    }

    for (size_t i = 0; i < size; i++) {
        input[i] = (int)(i + 1);
    }

    find_cubes(input, output, size);

    for (size_t i = 0; i < size; i++) {
        printf("%d ", output[i]);
    }
    printf("\n");

    free(input);
    free(output);

    return 0;
}