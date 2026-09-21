#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <inttypes.h>

typedef struct {
    int *elements;
    size_t size;
} Tuple;

Tuple create_tuple(const int *arr, size_t size) {
    Tuple t;
    t.elements = NULL;
    t.size = 0;
    
    if (arr == NULL || size == 0) {
        return t;
    }
    
    if (size > SIZE_MAX / sizeof(int)) {
        return t;
    }
    
    t.elements = malloc(size * sizeof(int));
    if (t.elements == NULL) {
        return t;
    }
    
    if (size > 0) {
        size_t bytes_to_copy = size * sizeof(int);
        if (bytes_to_copy <= size * sizeof(int) && bytes_to_copy <= SIZE_MAX) {
            memcpy(t.elements, arr, bytes_to_copy);
        } else {
            free(t.elements);
            t.elements = NULL;
            return t;
        }
    }
    
    t.size = size;
    return t;
}

void free_tuple(Tuple *t) {
    if (t == NULL) return;
    free(t->elements);
    t->elements = NULL;
    t->size = 0;
}

Tuple remove_duplicates(const Tuple *input) {
    Tuple result;
    result.elements = NULL;
    result.size = 0;
    
    if (input == NULL || input->elements == NULL || input->size == 0) {
        return result;
    }
    
    if (input->size > SIZE_MAX / sizeof(int)) {
        return result;
    }
    
    result.elements = malloc(input->size * sizeof(int));
    if (result.elements == NULL) {
        return result;
    }
    
    size_t unique_count = 0;
    for (size_t i = 0; i < input->size; i++) {
        int found = 0;
        for (size_t j = 0; j < unique_count; j++) {
            if (result.elements[j] == input->elements[i]) {
                found = 1;
                break;
            }
        }
        if (!found) {
            if (unique_count < input->size) {
                result.elements[unique_count++] = input->elements[i];
            }
        }
    }
    
    if (unique_count == 0) {
        free(result.elements);
        result.elements = NULL;
        result.size = 0;
        return result;
    }
    
    if (unique_count == input->size) {
        result.size = unique_count;
        return result;
    }
    
    int *temp = realloc(result.elements, unique_count * sizeof(int));
    if (temp == NULL) {
        free(result.elements);
        result.elements = NULL;
        result.size = 0;
        return result;
    }
    result.elements = temp;
    result.size = unique_count;
    return result;
}

int main(void) {
    int test_data[] = {1, 2, 2, 3, 4, 4, 4, 5, 1, 6};
    size_t test_size = sizeof(test_data) / sizeof(test_data[0]);
    
    Tuple input = create_tuple(test_data, test_size);
    if (input.elements == NULL) {
        fprintf(stderr, "Failed to create input tuple\n");
        return EXIT_FAILURE;
    }
    
    printf("Original tuple: ");
    for (size_t i = 0; i < input.size; i++) {
        printf("%d ", input.elements[i]);
    }
    printf("\n");
    
    Tuple result = remove_duplicates(&input);
    if (result.elements == NULL && input.size > 0) {
        fprintf(stderr, "Failed to remove duplicates\n");
        free_tuple(&input);
        return EXIT_FAILURE;
    }
    
    printf("After removing duplicates: ");
    for (size_t i = 0; i < result.size; i++) {
        printf("%d ", result.elements[i]);
    }
    printf("\n");
    
    free_tuple(&input);
    free_tuple(&result);
    
    return EXIT_SUCCESS;
}