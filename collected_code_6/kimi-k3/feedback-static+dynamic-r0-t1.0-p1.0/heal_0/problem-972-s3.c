#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    size_t size;
} Tuple;

typedef struct {
    Tuple *tuples;
    size_t count;
} NestedTuple;

Tuple* create_tuple(size_t size) {
    Tuple *t = (Tuple*)malloc(sizeof(Tuple));
    if (t == NULL) {
        return NULL;
    }
    t->data = (int*)malloc(size * sizeof(int));
    if (t->data == NULL) {
        free(t);
        return NULL;
    }
    t->size = size;
    return t;
}

void free_tuple(Tuple *t) {
    if (t != NULL) {
        free(t->data);
        free(t);
    }
}

NestedTuple* concatenate_tuples_to_nested(const Tuple *t1, const Tuple *t2) {
    if (t1 == NULL || t2 == NULL) {
        return NULL;
    }
    
    NestedTuple *nested = (NestedTuple*)malloc(sizeof(NestedTuple));
    if (nested == NULL) {
        return NULL;
    }
    
    nested->tuples = (Tuple*)malloc(2 * sizeof(Tuple));
    if (nested->tuples == NULL) {
        free(nested);
        return NULL;
    }
    
    nested->count = 2;
    
    nested->tuples[0].size = t1->size;
    nested->tuples[0].data = (int*)malloc(t1->size * sizeof(int));
    if (nested->tuples[0].data == NULL) {
        free(nested->tuples);
        free(nested);
        return NULL;
    }
    for (size_t i = 0; i < t1->size; i++) {
        nested->tuples[0].data[i] = t1->data[i];
    }
    
    nested->tuples[1].size = t2->size;
    nested->tuples[1].data = (int*)malloc(t2->size * sizeof(int));
    if (nested->tuples[1].data == NULL) {
        free(nested->tuples[0].data);
        free(nested->tuples);
        free(nested);
        return NULL;
    }
    for (size_t i = 0; i < t2->size; i++) {
        nested->tuples[1].data[i] = t2->data[i];
    }
    
    return nested;
}

void free_nested_tuple(NestedTuple *nested) {
    if (nested != NULL) {
        for (size_t i = 0; i < nested->count; i++) {
            free(nested->tuples[i].data);
        }
        free(nested->tuples);
        free(nested);
    }
}

void print_nested_tuple(const NestedTuple *nested) {
    if (nested == NULL) {
        return;
    }
    printf("(");
    for (size_t i = 0; i < nested->count; i++) {
        printf("(");
        for (size_t j = 0; j < nested->tuples[i].size; j++) {
            printf("%d", nested->tuples[i].data[j]);
            if (j < nested->tuples[i].size - 1) {
                printf(", ");
            }
        }
        printf(")");
        if (i < nested->count - 1) {
            printf(", ");
        }
    }
    printf(")\n");
}

int main(void) {
    Tuple *t1 = create_tuple(3);
    if (t1 == NULL) {
        return EXIT_FAILURE;
    }
    t1->data[0] = 1;
    t1->data[1] = 2;
    t1->data[2] = 3;
    
    Tuple *t2 = create_tuple(2);
    if (t2 == NULL) {
        free_tuple(t1);
        return EXIT_FAILURE;
    }
    t2->data[0] = 4;
    t2->data[1] = 5;
    
    NestedTuple *result = concatenate_tuples_to_nested(t1, t2);
    if (result == NULL) {
        free_tuple(t1);
        free_tuple(t2);
        return EXIT_FAILURE;
    }
    
    print_nested_tuple(result);
    
    free_tuple(t1);
    free_tuple(t2);
    free_nested_tuple(result);
    
    return EXIT_SUCCESS;
}