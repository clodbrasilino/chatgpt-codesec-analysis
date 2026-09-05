#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int a;
    int b;
    int c;
} Tuple;

Tuple* get_tuple_colon(const Tuple* t) {
    if (t == NULL) {
        return NULL;
    }
    Tuple* colon = malloc(sizeof(Tuple));
    if (colon == NULL) {
        return NULL;
    }
    colon->a = t->a;
    colon->b = t->b;
    colon->c = t->c;
    return colon;
}

int main(void) {
    Tuple original = {1, 2, 3};
    Tuple* cloned = get_tuple_colon(&original);
    
    if (cloned != NULL) {
        printf("%d %d %d\n", cloned->a, cloned->b, cloned->c);
        free(cloned);
    }
    
    return 0;
}