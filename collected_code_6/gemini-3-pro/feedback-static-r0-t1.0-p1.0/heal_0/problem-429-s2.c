#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    size_t size;
} Tuple;

Tuple* create_tuple(size_t size) {
    Tuple *t = (Tuple*)malloc(sizeof(Tuple));
    if (!t) return NULL;
    t->data = (int*)malloc(size * sizeof(int));
    if (!t->data) {
        free(t);
        return NULL;
    }
    t->size = size;
    return t;
}

void free_tuple(Tuple *t) {
    if (t) {
        if (t->data) {
            free(t->data);
        }
        free(t);
    }
}

Tuple* elementwise_and(const Tuple *t1, const Tuple *t2) {
    if (!t1 || !t2 || t1->size != t2->size) {
        return NULL;
    }
    
    Tuple *result = create_tuple(t1->size);
    if (!result) return NULL;
    
    for (size_t i = 0; i < t1->size; i++) {
        result->data[i] = t1->data[i] & t2->data[i];
    }
    
    return result;
}

int main() {
    size_t size = 4;
    Tuple *t1 = create_tuple(size);
    Tuple *t2 = create_tuple(size);
    
    if (!t1 || !t2) {
        free_tuple(t1);
        free_tuple(t2);
        return 1;
    }
    
    t1->data[0] = 12; t1->data[1] = 5;  t1->data[2] = 7;  t1->data[3] = 9;
    t2->data[0] = 10; t2->data[1] = 3;  t2->data[2] = 14; t2->data[3] = 8;
    
    Tuple *result = elementwise_and(t1, t2);
    
    if (result) {
        for (size_t i = 0; i < result->size; i++) {
            printf("%d ", result->data[i]);
        }
        printf("\n");
        free_tuple(result);
    }
    
    free_tuple(t1);
    free_tuple(t2);
    
    return 0;
}