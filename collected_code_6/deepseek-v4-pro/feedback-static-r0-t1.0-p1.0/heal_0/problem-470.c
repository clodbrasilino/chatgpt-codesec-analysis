#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *elements;
    int size;
} Tuple;

Tuple pairwise_add(const Tuple *t1, const Tuple *t2) {
    Tuple result;
    int min_size = (t1->size < t2->size) ? t1->size : t2->size;
    int max_size = (t1->size > t2->size) ? t1->size : t2->size;
    
    result.size = max_size;
    result.elements = (int *)malloc(max_size * sizeof(int));
    
    if (result.elements == NULL) {
        result.size = 0;
        return result;
    }
    
    for (int i = 0; i < min_size; i++) {
        result.elements[i] = t1->elements[i] + t2->elements[i];
    }
    
    if (min_size < max_size) {
        const Tuple *larger = (t1->size > t2->size) ? t1 : t2;
        for (int i = min_size; i < max_size; i++) {
            result.elements[i] = larger->elements[i];
        }
    }
    
    return result;
}

void free_tuple(Tuple *t) {
    if (t->elements != NULL) {
        free(t->elements);
        t->elements = NULL;
        t->size = 0;
    }
}

int main(void) {
    int elements1[] = {1, 2, 3, 4, 5};
    int elements2[] = {10, 20, 30};
    
    Tuple t1 = {elements1, 5};
    Tuple t2 = {elements2, 3};
    
    Tuple result = pairwise_add(&t1, &t2);
    
    if (result.elements == NULL && result.size == 0) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }
    
    for (int i = 0; i < result.size; i++) {
        printf("%d ", result.elements[i]);
    }
    printf("\n");
    
    free_tuple(&result);
    
    return EXIT_SUCCESS;
}