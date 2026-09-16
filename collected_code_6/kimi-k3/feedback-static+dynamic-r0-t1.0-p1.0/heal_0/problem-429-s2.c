#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    size_t size;
} Tuple;

Tuple create_tuple(size_t size) {
    Tuple t;
    t.size = size;
    t.data = malloc(size * sizeof(int));
    if (t.data == NULL) {
        t.size = 0;
    }
    return t;
}

void free_tuple(Tuple *t) {
    if (t != NULL && t->data != NULL) {
        free(t->data);
        t->data = NULL;
        t->size = 0;
    }
}

int elementwise_and(const Tuple *t1, const Tuple *t2, Tuple *result) {
    if (t1 == NULL || t2 == NULL || result == NULL) {
        return -1;
    }
    if (t1->size != t2->size || t1->data == NULL || t2->data == NULL) {
        return -1;
    }
    
    *result = create_tuple(t1->size);
    if (result->data == NULL && t1->size > 0) {
        return -1;
    }
    
    for (size_t i = 0; i < t1->size; i++) {
        result->data[i] = t1->data[i] & t2->data[i];
    }
    
    return 0;
}

int main(void) {
    Tuple t1 = create_tuple(5);
    Tuple t2 = create_tuple(5);
    Tuple result = {NULL, 0};
    
    if (t1.data == NULL || t2.data == NULL) {
        free_tuple(&t1);
        free_tuple(&t2);
        return EXIT_FAILURE;
    }
    
    t1.data[0] = 12;
    t1.data[1] = 10;
    t1.data[2] = 15;
    t1.data[3] = 8;
    t1.data[4] = 7;
    
    t2.data[0] = 10;
    t2.data[1] = 12;
    t2.data[2] = 7;
    t2.data[3] = 12;
    t2.data[4] = 15;
    
    if (elementwise_and(&t1, &t2, &result) != 0) {
        free_tuple(&t1);
        free_tuple(&t2);
        return EXIT_FAILURE;
    }
    
    printf("Result: ");
    for (size_t i = 0; i < result.size; i++) {
        printf("%d ", result.data[i]);
    }
    printf("\n");
    
    free_tuple(&t1);
    free_tuple(&t2);
    free_tuple(&result);
    
    return EXIT_SUCCESS;
}