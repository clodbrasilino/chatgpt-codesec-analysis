#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *elements;
    size_t size;
} Tuple;

typedef struct {
    Tuple *tuples;
    size_t size;
} NestedTuple;

NestedTuple* create_nested_tuple(size_t num_tuples) {
    NestedTuple *nt = malloc(sizeof(NestedTuple));
    if (nt == NULL) {
        return NULL;
    }
    nt->tuples = calloc(num_tuples, sizeof(Tuple));
    if (nt->tuples == NULL) {
        free(nt);
        return NULL;
    }
    nt->size = num_tuples;
    return nt;
}

int init_tuple(Tuple *t, size_t size) {
    if (t == NULL || size == 0) {
        return -1;
    }
    t->elements = calloc(size, sizeof(int));
    if (t->elements == NULL) {
        return -1;
    }
    t->size = size;
    return 0;
}

void free_nested_tuple(NestedTuple *nt) {
    if (nt != NULL) {
        if (nt->tuples != NULL) {
            for (size_t i = 0; i < nt->size; i++) {
                free(nt->tuples[i].elements);
            }
            free(nt->tuples);
        }
        free(nt);
    }
}

NestedTuple* add_nested_tuples(const NestedTuple *nt1, const NestedTuple *nt2) {
    if (nt1 == NULL || nt2 == NULL || nt1->size != nt2->size) {
        return NULL;
    }
    
    NestedTuple *result = create_nested_tuple(nt1->size);
    if (result == NULL) {
        return NULL;
    }
    
    for (size_t i = 0; i < nt1->size; i++) {
        if (nt1->tuples[i].size != nt2->tuples[i].size) {
            free_nested_tuple(result);
            return NULL;
        }
        
        if (init_tuple(&result->tuples[i], nt1->tuples[i].size) != 0) {
            free_nested_tuple(result);
            return NULL;
        }
        
        for (size_t j = 0; j < nt1->tuples[i].size; j++) {
            result->tuples[i].elements[j] = nt1->tuples[i].elements[j] + nt2->tuples[i].elements[j];
        }
    }
    
    return result;
}

void print_nested_tuple(const NestedTuple *nt) {
    if (nt == NULL) {
        printf("(null)\n");
        return;
    }
    printf("(");
    for (size_t i = 0; i < nt->size; i++) {
        printf("(");
        for (size_t j = 0; j < nt->tuples[i].size; j++) {
            printf("%d", nt->tuples[i].elements[j]);
            if (j < nt->tuples[i].size - 1) {
                printf(", ");
            }
        }
        printf(")");
        if (i < nt->size - 1) {
            printf(", ");
        }
    }
    printf(")\n");
}

int main(void) {
    NestedTuple *nt1 = create_nested_tuple(2);
    NestedTuple *nt2 = create_nested_tuple(2);
    
    if (nt1 == NULL || nt2 == NULL) {
        free_nested_tuple(nt1);
        free_nested_tuple(nt2);
        return EXIT_FAILURE;
    }
    
    if (init_tuple(&nt1->tuples[0], 2) != 0 || init_tuple(&nt1->tuples[1], 3) != 0 ||
        init_tuple(&nt2->tuples[0], 2) != 0 || init_tuple(&nt2->tuples[1], 3) != 0) {
        free_nested_tuple(nt1);
        free_nested_tuple(nt2);
        return EXIT_FAILURE;
    }
    
    nt1->tuples[0].elements[0] = 1;
    nt1->tuples[0].elements[1] = 2;
    nt1->tuples[1].elements[0] = 3;
    nt1->tuples[1].elements[1] = 4;
    nt1->tuples[1].elements[2] = 5;
    
    nt2->tuples[0].elements[0] = 10;
    nt2->tuples[0].elements[1] = 20;
    nt2->tuples[1].elements[0] = 30;
    nt2->tuples[1].elements[1] = 40;
    nt2->tuples[1].elements[2] = 50;
    
    printf("Tuple 1: ");
    print_nested_tuple(nt1);
    printf("Tuple 2: ");
    print_nested_tuple(nt2);
    
    NestedTuple *result = add_nested_tuples(nt1, nt2);
    if (result == NULL) {
        free_nested_tuple(nt1);
        free_nested_tuple(nt2);
        return EXIT_FAILURE;
    }
    
    printf("Result:  ");
    print_nested_tuple(result);
    
    free_nested_tuple(nt1);
    free_nested_tuple(nt2);
    free_nested_tuple(result);
    
    return EXIT_SUCCESS;
}