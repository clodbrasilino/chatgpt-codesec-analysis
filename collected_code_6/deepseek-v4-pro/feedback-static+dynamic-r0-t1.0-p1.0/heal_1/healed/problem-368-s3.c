#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int *data;
    size_t size;
} Tuple;

Tuple tuple_repeat(const Tuple *t, size_t n) {
    Tuple result;
    
    if (t == NULL || t->data == NULL || t->size == 0 || n == 0) {
        result.data = NULL;
        result.size = 0;
        return result;
    }
    
    if (n > SIZE_MAX / t->size) {
        result.data = NULL;
        result.size = 0;
        return result;
    }
    
    result.size = t->size * n;
    
    if (result.size > SIZE_MAX / sizeof(int)) {
        result.data = NULL;
        result.size = 0;
        return result;
    }
    
    result.data = (int *)malloc(result.size * sizeof(int));
    
    if (result.data == NULL) {
        result.size = 0;
        return result;
    }
    
    for (size_t i = 0; i < n; i++) {
        memcpy(result.data + i * t->size, t->data, t->size * sizeof(int));
    }
    
    return result;
}

void tuple_free(Tuple *t) {
    if (t != NULL) {
        if (t->data != NULL) {
            free(t->data);
            t->data = NULL;
        }
        t->size = 0;
    }
}

Tuple tuple_create(const int *values, size_t size) {
    Tuple t;
    
    if (size == 0 || values == NULL) {
        t.data = NULL;
        t.size = 0;
        return t;
    }
    
    if (size > SIZE_MAX / sizeof(int)) {
        t.data = NULL;
        t.size = 0;
        return t;
    }
    
    t.size = size;
    t.data = (int *)malloc(size * sizeof(int));
    
    if (t.data == NULL) {
        t.size = 0;
        return t;
    }
    
    memcpy(t.data, values, size * sizeof(int));
    
    return t;
}

int main(void) {
    const int values[] = {1, 2, 3};
    Tuple t = tuple_create(values, 3);
    
    if (t.data == NULL) {
        return 1;
    }
    
    Tuple repeated = tuple_repeat(&t, 4);
    
    if (repeated.data == NULL) {
        tuple_free(&t);
        return 1;
    }
    
    for (size_t i = 0; i < repeated.size; i++) {
        printf("%d ", repeated.data[i]);
    }
    printf("\n");
    
    tuple_free(&repeated);
    tuple_free(&t);
    
    return 0;
}