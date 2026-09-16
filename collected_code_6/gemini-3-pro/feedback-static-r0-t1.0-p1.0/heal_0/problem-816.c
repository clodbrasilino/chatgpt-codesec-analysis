#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int* data;
    size_t size;
} Tuple;

void clear_tuple(Tuple* t) {
    if (t == NULL) {
        return;
    }
    
    if (t->data != NULL) {
        free(t->data);
        t->data = NULL;
    }
    t->size = 0;
}

int main() {
    Tuple t;
    t.size = 5;
    t.data = (int*)malloc(t.size * sizeof(int));
    
    if (t.data == NULL) {
        return 1; 
    }
    
    for (size_t i = 0; i < t.size; i++) {
        t.data[i] = (int)(i + 1);
    }
    
    clear_tuple(&t);
    
    if (t.data == NULL && t.size == 0) {
        return 0;
    } else {
        return 1;
    }
}