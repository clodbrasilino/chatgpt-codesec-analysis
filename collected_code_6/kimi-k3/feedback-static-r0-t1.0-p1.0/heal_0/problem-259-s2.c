#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    size_t size;
} Tuple;

Tuple maximize_tuples(const Tuple *t1, const Tuple *t2) {
    Tuple result = {NULL, 0};
    size_t i;
    int cmp;
    
    if (t1 == NULL || t2 == NULL || t1->data == NULL || t2->data == NULL) {
        return result;
    }
    
    if (t1->size != t2->size) {
        return result;
    }
    
    if (t1->size == 0) {
        return result;
    }
    
    result.data = malloc(t1->size * sizeof(int));
    if (result.data == NULL) {
        return result;
    }
    
    result.size = t1->size;
    
    cmp = 0;
    for (i = 0; i < t1->size; i++) {
        if (t1->data[i] > t2->data[i]) {
            cmp = 1;
            break;
        } else if (t1->data[i] < t2->data[i]) {
            cmp = -1;
            break;
        }
    }
    
    if (cmp >= 0) {
        for (i = 0; i < t1->size; i++) {
            result.data[i] = t1->data[i];
        }
    } else {
        for (i = 0; i < t1->size; i++) {
            result.data[i] = t2->data[i];
        }
    }
    
    return result;
}

void free_tuple(Tuple *t) {
    if (t != NULL) {
        free(t->data);
        t->data = NULL;
        t->size = 0;
    }
}

int main(void) {
    int data1[] = {1, 5, 7};
    int data2[] = {1, 4, 9};
    Tuple t1 = {data1, 3};
    Tuple t2 = {data2, 3};
    Tuple max_tuple;
    size_t i;
    
    max_tuple = maximize_tuples(&t1, &t2);
    
    if (max_tuple.data == NULL) {
        fprintf(stderr, "Error: Failed to compute maximum tuple\n");
        return EXIT_FAILURE;
    }
    
    printf("Tuple 1: (");
    for (i = 0; i < t1.size; i++) {
        printf("%d%s", t1.data[i], (i < t1.size - 1) ? ", " : "");
    }
    printf(")\n");
    
    printf("Tuple 2: (");
    for (i = 0; i < t2.size; i++) {
        printf("%d%s", t2.data[i], (i < t2.size - 1) ? ", " : "");
    }
    printf(")\n");
    
    printf("Maximum tuple: (");
    for (i = 0; i < max_tuple.size; i++) {
        printf("%d%s", max_tuple.data[i], (i < max_tuple.size - 1) ? ", " : "");
    }
    printf(")\n");
    
    free_tuple(&max_tuple);
    
    return EXIT_SUCCESS;
}