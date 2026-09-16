#include <stdio.h>
#include <stdlib.h>

void square_elements(const int *input_list, int *output_list, size_t length) {
    if (input_list == NULL || output_list == NULL) {
        return;
    }

    for (size_t i = 0; i < length; ++i) {
        output_list[i] = input_list[i] * input_list[i];
    }
}

int main(void) {
    int input[] = {1, 2, 3, 4, 5};
    size_t length = sizeof(input) / sizeof(input[0]);
    int *output = (int *)malloc(length * sizeof(int));

    if (output == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    square_elements(input, output, length);

    for (size_t i = 0; i < length; ++i) {
        printf("%d ", output[i]);
    }
    printf("\n");

    free(output);
    output = NULL;

    return EXIT_SUCCESS;
}