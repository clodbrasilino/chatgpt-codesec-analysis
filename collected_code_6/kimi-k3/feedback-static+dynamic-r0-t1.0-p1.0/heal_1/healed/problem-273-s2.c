#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int *data;
    size_t size;
} Tuple;

int tuple_subtract(const Tuple *a, const Tuple *b, Tuple *result) {
    if (a == NULL || b == NULL || result == NULL) {
        return -1;
    }
    
    if (a->size != b->size) {
        return -1;
    }
    
    if (a->size == 0) {
        result->data = NULL;
        result->size = 0;
        return 0;
    }
    
    result->data = malloc(a->size * sizeof(int));
    if (result->data == NULL) {
        return -1;
    }
    
    result->size = a->size;
    
    for (size_t i = 0; i < a->size; i++) {
        result->data[i] = a->data[i] - b->data[i];
    }
    
    return 0;
}

void tuple_init(Tuple *t, const int *values, size_t size) {
    if (t == NULL) {
        return;
    }
    
    t->size = size;
    
    if (size == 0 || values == NULL) {
        t->data = NULL;
        return;
    }
    
    t->data = malloc(size * sizeof(int));
    if (t->data == NULL) {
        t->size = 0;
        return;
    }
    
    memcpy(t->data, values, size * sizeof(int));
}

void tuple_free(Tuple *t) {
    if (t == NULL) {
        return;
    }
    
    free(t->data);
    t->data = NULL;
    t->size = 0;
}

void tuple_print(const Tuple *t) {
    if (t == NULL || t->data == NULL) {
        printf("()\n");
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
    Tuple a, b, result;
    const int values_a[] = {10, 20, 30, 40};
    const int values_b[] = {1, 2, 3, 4};
    size_t size = sizeof(values_a) / sizeof(values_a[0]);
    
    tuple_init(&a, values_a, size);
    tuple_init(&b, values_b, size);
    
    if (tuple_subtract(&a, &b, &result) != 0) {
        fprintf(stderr, "Error: tuple subtraction failed\n");
        tuple_free(&a);
        tuple_free(&b);
        return EXIT_FAILURE;
    }
    
    printf("Tuple A: ");
    tuple_print(&a);
    
    printf("Tuple B: ");
    tuple_print(&b);
    
    printf("Result (A - B): ");
    tuple_print(&result);
    
    tuple_free(&a);
    tuple_free(&b);
    tuple_free(&result);
    
    return EXIT_SUCCESS;
}