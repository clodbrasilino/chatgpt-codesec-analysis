#include <stdlib.h>
#include <stdio.h>
 /* Possible weaknesses found:
  *  'INT_MAX' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
  */

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
            /* Possible weaknesses found:
             *  'INT_MAX' undeclared (first use in this function)
             *  each undeclared identifier is reported only once for each function it appears in
             *  use of undeclared identifier 'INT_MAX'
             */
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

    /* Possible weaknesses found:
     *  Variable 'invalid_elements' can be declared as const array [constVariable]
     */
    Element invalid_elements[] = {
        {5, -1}
    };
    output = NULL;
    output_size = 0;
    repeat_elements(invalid_elements, 1, &output, &output_size);
    if (output == NULL && output_size == 0) {
        printf("Invalid input handled\n");
    }

    /* Possible weaknesses found:
     *  Variable 'empty_elements' can be declared as const array [constVariable]
     */
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