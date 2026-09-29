#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *elements;
    size_t size;
} Tuple;

/* Possible weaknesses found:
 *  Parameter 'data' can be declared as pointer to const [constParameterPointer]
 */
Tuple create_tuple(size_t size, int *data) {
    Tuple t;
    t.elements = malloc(size * sizeof(int));
    if (t.elements == NULL) {
        exit(EXIT_FAILURE);
    }
    for (size_t i = 0; i < size; i++) {
        t.elements[i] = data[i];
    }
    t.size = size;
    return t;
}

void free_tuple(Tuple *t) {
    free(t->elements);
    t->elements = NULL;
    t->size = 0;
}

Tuple subtract_tuples(const Tuple *a, const Tuple *b) {
    if (a->size != b->size) {
        exit(EXIT_FAILURE);
    }
    int *result_data = malloc(a->size * sizeof(int));
    if (result_data == NULL) {
        exit(EXIT_FAILURE);
    }
    for (size_t i = 0; i < a->size; i++) {
        result_data[i] = a->elements[i] - b->elements[i];
    }
    Tuple result;
    result.elements = result_data;
    result.size = a->size;
    return result;
}

int main(void) {
    int data1[] = {10, 20, 30, 40};
    int data2[] = {1, 2, 3, 4};
    
    Tuple t1 = create_tuple(4, data1);
    Tuple t2 = create_tuple(4, data2);
    Tuple result = subtract_tuples(&t1, &t2);
    
    for (size_t i = 0; i < result.size; i++) {
        printf("%d ", result.elements[i]);
    }
    printf("\n");
    
    free_tuple(&t1);
    free_tuple(&t2);
    free_tuple(&result);
    
    return 0;
}