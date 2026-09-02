#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int size;
    int *elements;
} Tuple;

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as const array [constParameter]
 */
Tuple* create_tuple(int n, int arr[]) {
    Tuple *t = (Tuple*)malloc(sizeof(Tuple));
    t->size = n;
    t->elements = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; ++i) {
        t->elements[i] = arr[i];
    }
    return t;
}

void free_tuple(Tuple *t) {
    free(t->elements);
    free(t);
}

Tuple* multiply_tuples(Tuple *a, Tuple *b) {
    /* Possible weaknesses found:
     *  Either the condition 'a==NULL' is redundant or there is possible null pointer dereference: a. [nullPointerRedundantCheck]
     *  Assuming that condition 'a==NULL' is not redundant
     *  Null pointer dereference
     *  Assuming that condition 'b==NULL' is not redundant
     *  Either the condition 'b==NULL' is redundant or there is possible null pointer dereference: b. [nullPointerRedundantCheck]
     */
    if (a->size != b->size || a == NULL || b == NULL) {
        return NULL;
    }

    Tuple *result = (Tuple*)malloc(sizeof(Tuple));
    result->size = a->size;
    result->elements = (int*)malloc(result->size * sizeof(int));

    for (int i = 0; i < result->size; ++i) {
        result->elements[i] = a->elements[i] * b->elements[i];
    }

    return result;
}

int main() {
    int arr1[] = {2, 3, 4};
    int arr2[] = {5, 6, 7};

    Tuple *t1 = create_tuple(3, arr1);
    Tuple *t2 = create_tuple(3, arr2);

    Tuple *result = multiply_tuples(t1, t2);

    if (result != NULL) {
        for (int i = 0; i < result->size; ++i) {
            printf("%d ", result->elements[i]);
        }
        printf("\n");
    } else {
        printf("Invalid tuples\n");
    }

    free_tuple(t1);
    free_tuple(t2);
    if (result != NULL) {
        free_tuple(result);
    }

    return 0;
}