#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    size_t size;
} Tuple;

void free_tuple(Tuple *t) {
    if (t != NULL) {
        free(t->data);
        t->data = NULL;
        t->size = 0;
    }
}

int init_tuple(Tuple *t, const int *values, size_t size) {
    if (t == NULL || (values == NULL && size > 0)) {
        return -1;
    }
    
    t->size = size;
    if (size == 0) {
        t->data = NULL;
        return 0;
    }
    
    t->data = malloc(size * sizeof(int));
    if (t->data == NULL) {
        t->size = 0;
        return -1;
    }
    
    for (size_t i = 0; i < size; i++) {
        t->data[i] = values[i];
    }
    
    return 0;
}

int extract_elementwise_and(const Tuple *t1, const Tuple *t2, Tuple *result) {
    if (t1 == NULL || t2 == NULL || result == NULL) {
        return -1;
    }
    
    if (t1->size != t2->size) {
        return -1;
    }
    
    if (t1->size == 0) {
        result->data = NULL;
        result->size = 0;
        return 0;
    }
    
    if (t1->data == NULL || t2->data == NULL) {
        return -1;
    }
    
    result->size = t1->size;
    result->data = malloc(result->size * sizeof(int));
    if (result->data == NULL) {
        result->size = 0;
        return -1;
    }
    
    for (size_t i = 0; i < t1->size; i++) {
        result->data[i] = t1->data[i] & t2->data[i];
    }
    
    return 0;
}

void print_tuple(const Tuple *t) {
    if (t == NULL) {
        printf("NULL\n");
        return;
    }
    
    printf("(");
    for (size_t i = 0; i < t->size; i++) {
        printf("%d", t->data[i]);
        if (i < t->size - 1) {
            printf(", ");
        }
    }
    printf(")\n");
}

int main(void) {
    Tuple t1 = {0};
    Tuple t2 = {0};
    Tuple result = {0};
    int status = 0;
    
    const int values1[] = {1, 2, 3, 4};
    const int values2[] = {1, 1, 0, 5};
    size_t size = sizeof(values1) / sizeof(values1[0]);
    
    if (init_tuple(&t1, values1, size) != 0) {
        fprintf(stderr, "Failed to initialize tuple 1\n");
        status = 1;
        goto cleanup;
    }
    
    if (init_tuple(&t2, values2, size) != 0) {
        fprintf(stderr, "Failed to initialize tuple 2\n");
        status = 1;
        goto cleanup;
    }
    
    if (extract_elementwise_and(&t1, &t2, &result) != 0) {
        fprintf(stderr, "Failed to extract elementwise AND\n");
        status = 1;
        goto cleanup;
    }
    
    printf("Tuple 1: ");
    print_tuple(&t1);
    printf("Tuple 2: ");
    print_tuple(&t2);
    printf("Elementwise AND: ");
    print_tuple(&result);
    
cleanup:
    free_tuple(&t1);
    free_tuple(&t2);
    free_tuple(&result);
    
    return status;
}