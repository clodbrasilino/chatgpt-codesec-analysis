#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int* data;
    size_t size;
} Tuple;

Tuple* create_tuple(int* elements, size_t size) {
    Tuple* tuple = (Tuple*)malloc(sizeof(Tuple));
    if (!tuple) return NULL;
    tuple->data = (int*)malloc(size * sizeof(int));
    if (!tuple->data) {
        free(tuple);
        return NULL;
    }
    memcpy(tuple->data, elements, size * sizeof(int));
    tuple->size = size;
    return tuple;
}

void free_tuple(Tuple* tuple) {
    if (tuple) {
        free(tuple->data);
        free(tuple);
    }
}
 /* Possible weaknesses found:
  *  test case 0 failed: expected '[(2,), (9,), (2,), (2,)]', got (null)
  *  test case 2 failed: expected '[(8, 4), (8, 12), (1, 7), (6, 9)]', got (null)
  *  test case 1 failed: expected '[(3, 2, 1), (4, 9, 2), (1, 2, 3), (8, 2, 1)]', got (null)
  */

Tuple* trim_tuple_by_k(Tuple* tuple, int k) {
    if (k < 0 || k > (int)tuple->size) return NULL;
    Tuple* trimmed = (Tuple*)malloc(sizeof(Tuple));
    if (!trimmed) return NULL;
    trimmed->size = tuple->size - k;
    trimmed->data = (int*)malloc(trimmed->size * sizeof(int));
    if (!trimmed->data) {
        free(trimmed);
        return NULL;
    }
    for (int i = k; i < (int)tuple->size; ++i) {
        trimmed->data[i - k] = tuple->data[i];
    }
    return trimmed;
}

int main() {
    int elements[] = {1, 2, 3, 4, 5};
    size_t size = sizeof(elements) / sizeof(elements[0]);
    
    Tuple* tuple = create_tuple(elements, size);
    if (!tuple) {
        printf("Failed to create tuple\n");
        return 1;
    }
    
    int k = 2;
    Tuple* trimmed = trim_tuple_by_k(tuple, k);
    if (!trimmed) {
        printf("Failed to trim tuple\n");
        free_tuple(tuple);
        return 1;
    }
    
    for (size_t i = 0; i < trimmed->size; ++i) {
        printf("%d ", trimmed->data[i]);
    }
    printf("\n");

    free_tuple(trimmed);
    free_tuple(tuple);
    return 0;
}