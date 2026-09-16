#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int *data;
    size_t size;
} Tuple;

typedef struct {
    Tuple **tuples;
    size_t size;
} NestedTuple;

Tuple *create_tuple(const int *data, size_t size) {
    Tuple *t = malloc(sizeof(Tuple));
    if (t == NULL) {
        return NULL;
    }
    t->size = size;
    if (size > 0 && data != NULL) {
        t->data = malloc(size * sizeof(int));
        if (t->data == NULL) {
            free(t);
            return NULL;
        }
        memcpy(t->data, data, size * sizeof(int));
    } else {
        t->data = NULL;
    }
    return t;
}

NestedTuple *concat_to_nested(const Tuple *t1, const Tuple *t2) {
    if (t1 == NULL || t2 == NULL) {
        return NULL;
    }
    NestedTuple *nt = malloc(sizeof(NestedTuple));
    if (nt == NULL) {
        return NULL;
    }
    nt->size = 2;
    nt->tuples = malloc(2 * sizeof(Tuple *));
    if (nt->tuples == NULL) {
        free(nt);
        return NULL;
    }
    nt->tuples[0] = create_tuple(t1->data, t1->size);
    if (nt->tuples[0] == NULL) {
        free(nt->tuples);
        free(nt);
        return NULL;
    }
    nt->tuples[1] = create_tuple(t2->data, t2->size);
    if (nt->tuples[1] == NULL) {
        free(nt->tuples[0]->data);
        free(nt->tuples[0]);
        free(nt->tuples);
        free(nt);
        return NULL;
    }
    return nt;
}

void free_tuple(Tuple *t) {
    if (t != NULL) {
        free(t->data);
        free(t);
    }
}

void free_nested_tuple(NestedTuple *nt) {
    if (nt != NULL) {
        if (nt->tuples != NULL) {
            for (size_t i = 0; i < nt->size; i++) {
                free_tuple(nt->tuples[i]);
            }
            free(nt->tuples);
        }
        free(nt);
    }
}

void print_tuple(const Tuple *t) {
    if (t == NULL) {
        printf("()");
        return;
    }
    printf("(");
    for (size_t i = 0; i < t->size; i++) {
        printf("%d", t->data[i]);
        if (i < t->size - 1) {
            printf(", ");
        }
    }
    printf(")");
}

void print_nested_tuple(const NestedTuple *nt) {
    if (nt == NULL) {
        printf("()");
        return;
    }
    printf("(");
    for (size_t i = 0; i < nt->size; i++) {
        print_tuple(nt->tuples[i]);
        if (i < nt->size - 1) {
            printf(", ");
        }
    }
    printf(")");
}

int main(void) {
    /* Possible weaknesses found:
     *  Variable 'data1' can be declared as const array [constVariable]
     */
    int data1[] = {1, 2, 3};
    /* Possible weaknesses found:
     *  Variable 'data2' can be declared as const array [constVariable]
     */
    int data2[] = {4, 5, 6};
    
    Tuple *t1 = create_tuple(data1, 3);
    if (t1 == NULL) {
        fprintf(stderr, "Failed to create tuple 1\n");
        return EXIT_FAILURE;
    }
    
    Tuple *t2 = create_tuple(data2, 3);
    if (t2 == NULL) {
        fprintf(stderr, "Failed to create tuple 2\n");
        free_tuple(t1);
        return EXIT_FAILURE;
    }
    
    NestedTuple *result = concat_to_nested(t1, t2);
    if (result == NULL) {
        fprintf(stderr, "Failed to concatenate tuples\n");
        free_tuple(t1);
        free_tuple(t2);
        return EXIT_FAILURE;
    }
    
    printf("Tuple 1: ");
    print_tuple(t1);
    printf("\n");
    
    printf("Tuple 2: ");
    print_tuple(t2);
    printf("\n");
    
    printf("Nested Tuple: ");
    print_nested_tuple(result);
    printf("\n");
    
    free_tuple(t1);
    free_tuple(t2);
    free_nested_tuple(result);
    
    return EXIT_SUCCESS;
}