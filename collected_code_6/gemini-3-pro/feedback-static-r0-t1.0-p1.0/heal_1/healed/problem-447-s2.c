#include <stdio.h>
#include <stdlib.h>

int compute_cubes(const int *input, int *output, size_t size) {
    if (input == NULL || output == NULL) {
        return -1;
    }

    for (size_t i = 0; i < size; i++) {
        output[i] = input[i] * input[i] * input[i];
    }

    return 0;
}

int main(void) {
    int input_list[] = {1, 2, 3, 4, 5, -2, -3};
    size_t size = sizeof(input_list) / sizeof(input_list[0]);
    
    int *output_list = (int *)malloc(size * sizeof(int));
    if (output_list == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    if (compute_cubes(input_list, output_list, size) != 0) {
        fprintf(stderr, "Failed to compute cubes\n");
        free(output_list);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < size; i++) {
        printf("%d\n", output_list[i]);
    }

    free(output_list);
    output_list = NULL;

    return EXIT_SUCCESS;
}