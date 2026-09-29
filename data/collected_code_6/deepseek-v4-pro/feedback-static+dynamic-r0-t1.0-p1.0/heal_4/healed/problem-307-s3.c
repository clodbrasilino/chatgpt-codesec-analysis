#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct {
    void **elements;
    size_t size;
} Tuple;

void *tuple_get_colon(Tuple *tuple, size_t start, size_t end) {
    if (tuple == NULL || tuple->elements == NULL) {
        return NULL;
    }
    
    if (start >= tuple->size || end > tuple->size || start >= end) {
        return NULL;
    }
    
    size_t colon_size = end - start;
    
    if (colon_size > (SIZE_MAX / sizeof(void *))) {
        return NULL;
    }
    
    size_t alloc_size = colon_size * sizeof(void *);
    void **colon = (void **)malloc(alloc_size);
    if (colon == NULL) {
        return NULL;
    }
    
    if (alloc_size > 0) {
        if (start + colon_size > tuple->size) {
            free(colon);
            return NULL;
        }
        memcpy(colon, &(tuple->elements[start]), alloc_size);
    }
    
    return colon;
}

int main(void) {
    int a = 10, b = 20, c = 30, d = 40, e = 50;
    void *elements[] = {&a, &b, &c, &d, &e};
    
    Tuple tuple;
    tuple.elements = elements;
    tuple.size = 5;
    
    void **colon = (void **)tuple_get_colon(&tuple, 1, 4);
    
    if (colon != NULL) {
        for (size_t i = 0; i < 3; i++) {
            printf("%d ", *(int *)colon[i]);
        }
        printf("\n");
        free(colon);
    }
    
    return 0;
}