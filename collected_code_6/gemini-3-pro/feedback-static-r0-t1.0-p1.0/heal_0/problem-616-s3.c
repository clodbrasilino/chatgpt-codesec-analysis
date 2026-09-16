#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *elements;
    size_t size;
} Tuple;

int modulo_tuples(const Tuple *t1, const Tuple *t2, Tuple *result) {
    if (!t1 || !t2 || !result || !t1->elements || !t2->elements || t1->size != t2->size) {
        return -1;
    }

    result->size = t1->size;
    result->elements = (int *)malloc(result->size * sizeof(int));
    if (!result->elements) {
        return -1;
    }

    for (size_t i = 0; i < t1->size; ++i) {
        if (t2->elements[i] == 0) {
            free(result->elements);
            result->elements = NULL;
            result->size = 0;
            return -1; 
        }
        result->elements[i] = t1->elements[i] % t2->elements[i];
    }

    return 0;
}

int main(void) {
    int elems1[] = {10, 20, 30, 40};
    int elems2[] = {3, 7, 4, 9};

    Tuple t1 = {elems1, 4};
    Tuple t2 = {elems2, 4};
    Tuple result = {NULL, 0};

    if (modulo_tuples(&t1, &t2, &result) == 0) {
        for (size_t i = 0; i < result.size; ++i) {
            printf("%d ", result.elements[i]);
        }
        printf("\n");
        free(result.elements);
    } else {
        printf("Error performing modulo on tuples.\n");
    }

    return 0;
}