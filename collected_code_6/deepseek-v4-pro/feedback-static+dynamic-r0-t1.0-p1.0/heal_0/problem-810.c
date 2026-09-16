#include <stdlib.h>
#include <stdio.h>

typedef struct {
    int value;
    int count;
} Element;

void repeat_elements(const Element *elements, int num_elements, int **output, int *output_size) {
    if (elements == NULL || output == NULL || output_size == NULL) {
        return;
    }

    int total = 0;
    for (int i = 0; i < num_elements; i++) {
        if (elements[i].count < 0) {
            return;
        }
        if (elements[i].count > 0) {
            int remaining = INT_MAX - total;
            if (elements[i].count > remaining) {
                return;
            }
            total += elements[i].count;
        }
    }

    if (total == 0) {
        *output = NULL;
        *output_size = 0;
        return;
    }

    int *result = malloc((size_t)total * sizeof(int));
    if (result == NULL) {
        return;
    }

    int index = 0;
    for (int i = 0; i < num_elements; i++) {
        for (int j = 0; j < elements[i].count; j++) {
            result[index++] = elements[i].value;
        }
    }

    *output = result;
    *output_size = total;
}

int main(void) {
    Element elements[] = {
        {1, 3},
        {2, 2},
        {3, 1},
        {4, 0}
    };
    int num_elements = sizeof(elements) / sizeof(elements[0]);
    int *output = NULL;
    int output_size = 0;

    repeat_elements(elements, num_elements, &output, &output_size);

    if (output != NULL) {
        for (int i = 0; i < output_size; i++) {
            printf("%d ", output[i]);
        }
        printf("\n");
        free(output);
    }
    else if (output_size == 0) {
        printf("Empty output\n");
    }
    else {
        printf("Error occurred\n");
    }

    Element invalid_elements[] = {
        {5, -1}
    };
    output = NULL;
    output_size = 0;
    repeat_elements(invalid_elements, 1, &output, &output_size);
    if (output == NULL && output_size == 0) {
        printf("Invalid input handled\n");
    }

    Element empty_elements[] = {
        {6, 0},
        {7, 0}
    };
    output = NULL;
    output_size = 0;
    repeat_elements(empty_elements, 2, &output, &output_size);
    if (output == NULL && output_size == 0) {
        printf("Empty input handled\n");
    }

    return 0;
}