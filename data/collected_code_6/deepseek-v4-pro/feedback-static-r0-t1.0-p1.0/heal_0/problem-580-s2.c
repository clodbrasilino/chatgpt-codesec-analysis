#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Tuple {
    void **elements;
    int *types;
    int size;
} Tuple;

int *extract_even_elements(Tuple *tuple, int *result_size) {
    if (tuple == NULL || result_size == NULL) {
        return NULL;
    }

    int *even_elements = NULL;
    int count = 0;
    int capacity = 0;

    for (int i = 0; i < tuple->size; i++) {
        if (tuple->types[i] == 0) {
            int value = *(int *)tuple->elements[i];
            if (value % 2 == 0) {
                if (count >= capacity) {
                    capacity = capacity == 0 ? 4 : capacity * 2;
                    int *new_array = realloc(even_elements, capacity * sizeof(int));
                    if (new_array == NULL) {
                        free(even_elements);
                        return NULL;
                    }
                    even_elements = new_array;
                }
                even_elements[count++] = value;
            }
        } else if (tuple->types[i] == 1) {
            Tuple *nested_tuple = (Tuple *)tuple->elements[i];
            int nested_size = 0;
            int *nested_even = extract_even_elements(nested_tuple, &nested_size);
            if (nested_even != NULL) {
                for (int j = 0; j < nested_size; j++) {
                    if (count >= capacity) {
                        capacity = capacity == 0 ? 4 : capacity * 2;
                        int *new_array = realloc(even_elements, capacity * sizeof(int));
                        if (new_array == NULL) {
                            free(nested_even);
                            free(even_elements);
                            return NULL;
                        }
                        even_elements = new_array;
                    }
                    even_elements[count++] = nested_even[j];
                }
                free(nested_even);
            }
        }
    }

    *result_size = count;
    return even_elements;
}

int main(void) {
    int a = 2, b = 3, c = 4;
    int d = 5, e = 6;

    void *outer_elements[] = {&a, &b, NULL, &c, &d};
    int outer_types[] = {0, 0, 1, 0, 0};

    void *inner_elements[] = {&e, &d, &b};
    int inner_types[] = {0, 0, 0};

    Tuple inner_tuple = {
        .elements = inner_elements,
        .types = inner_types,
        .size = 3
    };

    outer_elements[2] = &inner_tuple;

    Tuple outer_tuple = {
        .elements = outer_elements,
        .types = outer_types,
        .size = 5
    };

    int result_size = 0;
    int *result = extract_even_elements(&outer_tuple, &result_size);

    if (result != NULL) {
        for (int i = 0; i < result_size; i++) {
            printf("%d ", result[i]);
        }
        printf("\n");
        free(result);
    } else {
        printf("Memory allocation failed\n");
    }

    return 0;
}