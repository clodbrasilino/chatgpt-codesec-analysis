#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int value;
    int count;
} Element;

int repeat_elements(const Element *input, int input_size, int **output, int *output_size) {
    if (input == NULL || output == NULL || output_size == NULL || input_size < 0) {
        return -1;
    }

    int total_size = 0;
    for (int i = 0; i < input_size; i++) {
        if (input[i].count < 0) {
            return -1;
        }
        if (input[i].count > 0 && (size_t)total_size + (size_t)input[i].count > (size_t)-2) {
            return -1;
        }
        total_size += input[i].count;
    }

    if (total_size == 0) {
        *output = NULL;
        *output_size = 0;
        return 0;
    }

    int *result = (int *)malloc((size_t)total_size * sizeof(int));
    if (result == NULL) {
        return -1;
    }

    int index = 0;
    for (int i = 0; i < input_size; i++) {
        for (int j = 0; j < input[i].count; j++) {
            result[index++] = input[i].value;
        }
    }

    *output = result;
    *output_size = total_size;
    return 0;
}

int main(void) {
    Element elements[] = {
        {1, 2},
        {2, 3},
        {3, 1},
        {4, 0}
    };
    int input_size = sizeof(elements) / sizeof(elements[0]);
    int *output = NULL;
    int output_size = 0;

    int result = repeat_elements(elements, input_size, &output, &output_size);
    if (result != 0) {
        printf("Error processing elements\n");
        return 1;
    }

    for (int i = 0; i < output_size; i++) {
        printf("%d ", output[i]);
    }
    printf("\n");

    free(output);
    output = NULL;

    return 0;
}