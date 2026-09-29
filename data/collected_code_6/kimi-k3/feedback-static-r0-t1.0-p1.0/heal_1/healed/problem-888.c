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

int subtract_nested_tuples(const NestedTuple *nt1, const NestedTuple *nt2, NestedTuple *result) {
    size_t i, j;
    
    if (nt1 == NULL || nt2 == NULL || result == NULL) {
        return -1;
    }
    
    if (nt1->size != nt2->size) {
        return -1;
    }
    
    result->size = nt1->size;
    result->tuples = (Tuple *)malloc(result->size * sizeof(Tuple));
    if (result->tuples == NULL) {
        return -1;
    }
    
    for (i = 0; i < nt1->size; i++) {
        if (nt1->tuples[i].size != nt2->tuples[i].size) {
            for (j = 0; j < i; j++) {
                free(result->tuples[j].elements);
            }
            free(result->tuples);
            result->tuples = NULL;
            result->size = 0;
            return -1;
        }
        
        result->tuples[i].size = nt1->tuples[i].size;
        result->tuples[i].elements = (int *)malloc(result->tuples[i].size * sizeof(int));
        
        if (result->tuples[i].elements == NULL) {
            for (j = 0; j < i; j++) {
                free(result->tuples[j].elements);
            }
            free(result->tuples);
            result->tuples = NULL;
            result->size = 0;
            return -1;
        }
        
        for (j = 0; j < nt1->tuples[i].size; j++) {
            result->tuples[i].elements[j] = nt1->tuples[i].elements[j] - nt2->tuples[i].elements[j];
        }
    }
    
    return 0;
}

void free_nested_tuple(NestedTuple *nt) {
    if (nt == NULL) {
        return;
    }
    
    if (nt->tuples != NULL) {
        for (size_t i = 0; i < nt->size; i++) {
            free(nt->tuples[i].elements);
            nt->tuples[i].elements = NULL;
        }
        free(nt->tuples);
        nt->tuples = NULL;
    }
    nt->size = 0;
}

int init_nested_tuple(NestedTuple *nt, size_t outer_size, const size_t *inner_sizes, const int *values) {
    size_t i, j;
    size_t value_idx = 0;
    
    if (nt == NULL || inner_sizes == NULL || values == NULL) {
        return -1;
    }
    
    nt->size = outer_size;
    nt->tuples = (Tuple *)malloc(outer_size * sizeof(Tuple));
    if (nt->tuples == NULL) {
        return -1;
    }
    
    for (i = 0; i < outer_size; i++) {
        nt->tuples[i].size = inner_sizes[i];
        nt->tuples[i].elements = (int *)malloc(inner_sizes[i] * sizeof(int));
        
        if (nt->tuples[i].elements == NULL) {
            for (j = 0; j < i; j++) {
                free(nt->tuples[j].elements);
            }
            free(nt->tuples);
            nt->tuples = NULL;
            nt->size = 0;
            return -1;
        }
        
        for (j = 0; j < inner_sizes[i]; j++) {
            nt->tuples[i].elements[j] = values[value_idx++];
        }
    }
    
    return 0;
}

void print_nested_tuple(const NestedTuple *nt) {
    size_t i, j;
    
    if (nt == NULL || nt->tuples == NULL) {
        printf("()\n");
        return;
    }
    
    printf("(");
    for (i = 0; i < nt->size; i++) {
        printf("(");
        for (j = 0; j < nt->tuples[i].size; j++) {
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
    NestedTuple nt1 = {0};
    NestedTuple nt2 = {0};
    NestedTuple result = {0};
    const size_t inner_sizes[] = {2, 3, 2};
    const int values1[] = {10, 20, 30, 40, 50, 60, 70};
    const int values2[] = {1, 2, 3, 4, 5, 6, 7};
    int status;
    
    status = init_nested_tuple(&nt1, 3, inner_sizes, values1);
    if (status != 0) {
        fprintf(stderr, "Failed to initialize first nested tuple\n");
        return EXIT_FAILURE;
    }
    
    status = init_nested_tuple(&nt2, 3, inner_sizes, values2);
    if (status != 0) {
        fprintf(stderr, "Failed to initialize second nested tuple\n");
        free_nested_tuple(&nt1);
        return EXIT_FAILURE;
    }
    
    printf("First nested tuple: ");
    print_nested_tuple(&nt1);
    
    printf("Second nested tuple: ");
    print_nested_tuple(&nt2);
    
    status = subtract_nested_tuples(&nt1, &nt2, &result);
    if (status != 0) {
        fprintf(stderr, "Failed to subtract nested tuples\n");
        free_nested_tuple(&nt1);
        free_nested_tuple(&nt2);
        return EXIT_FAILURE;
    }
    
    printf("Result: ");
    print_nested_tuple(&result);
    
    free_nested_tuple(&nt1);
    free_nested_tuple(&nt2);
    free_nested_tuple(&result);
    
    return EXIT_SUCCESS;
}