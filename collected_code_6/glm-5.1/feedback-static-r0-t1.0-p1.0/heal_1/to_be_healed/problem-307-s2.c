#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int a;
    int b;
} Tuple;

Tuple* get_colon(const Tuple* src) {
    Tuple* dst = NULL;

    if (src == NULL) {
        return NULL;
    }

    dst = (Tuple*)malloc(sizeof(Tuple));
    if (dst == NULL) {
        return NULL;
    }

    dst->a = src->a;
    dst->b = src->b;

    return dst;
}

int main(void) {
    Tuple original = {10, 20};
    Tuple* cloned = get_colon(&original);

    if (cloned != NULL) {
        printf("Original: (%d, %d)\n", original.a, original.b);
        printf("Cloned:   (%d, %d)\n", cloned->a, cloned->b);
        free(cloned);
    }

    /* Possible weaknesses found:
     *  Variable 'null_cloned' can be declared as pointer to const [constVariablePointer]
     */
    Tuple* null_cloned = get_colon(NULL);
    if (null_cloned == NULL) {
        printf("Successfully handled NULL input.\n");
    }

    return 0;
}