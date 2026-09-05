#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    size_t size;
} Tuple;

Tuple multiply_tuples(const Tuple *t1, const Tuple *t2) {
    Tuple result = {NULL, 0};
    size_t i;
    
    if (t1 == NULL || t2 == NULL || t1->data == NULL || t2->data == NULL) {
        return result;
    }
    
    if (t1->size != t2->size || t1->size == 0) {
        return result;
    }
    
    result.data = (int *)malloc(t1->size * sizeof(int));
    if (result.data == NULL) {
        return result;
    }
    
    result.size = t1->size;
    
    for (i = 0; i < t1->size; i++) {
        result.data[i] = t1->data[i] * t2->data[i];
    }
    
    return result;
}

void free_tuple(Tuple *t) {
    if (t != NULL && t->data != NULL) {
        free(t->data);
        t->data = NULL;
        t->size = 0;
    }
}

int main(void) {
    int arr1[] = {1, 2, 3, 4, 5};
    int arr2[] = {6, 7, 8, 9, 10};
    /* Possible weaknesses found:
     *  The scope of the variable 'i' can be reduced. [variableScope]
     */
    size_t i;
    
    Tuple t1 = {arr1, 5};
    Tuple t2 = {arr2, 5};
    
    Tuple result = multiply_tuples(&t1, &t2);
    
    if (result.data != NULL) {
        printf("Result: ");
        for (i = 0; i < result.size; i++) {
            printf("%d ", result.data[i]);
        }
        printf("\n");
        
        free_tuple(&result);
    } else {
        printf("Error: Tuple multiplication failed\n");
        return 1;
    }
    
    return 0;
}