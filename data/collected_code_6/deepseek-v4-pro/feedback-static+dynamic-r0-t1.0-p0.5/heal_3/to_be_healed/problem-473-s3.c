#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int *elements;
    int size;
} Tuple;

typedef struct {
    Tuple *tuples;
    int count;
} TupleList;

int compare_ints(const void *a, const void *b) {
    int arg1 = *(const int *)a;
    int arg2 = *(const int *)b;
    return (arg1 > arg2) - (arg1 < arg2);
}

int *copy_sorted_tuple(const Tuple *tuple) {
    if (tuple == NULL || tuple->elements == NULL || tuple->size <= 0) {
        return NULL;
    }
    
    size_t alloc_size = (size_t)tuple->size * sizeof(int);
    if (alloc_size / sizeof(int) != (size_t)tuple->size) {
        return NULL;
    }
    
    int *sorted = (int *)malloc(alloc_size);
    if (sorted == NULL) {
        return NULL;
    }
    
    if (tuple->size > 0) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(sorted, tuple->elements, alloc_size);
    }
    
    qsort(sorted, tuple->size, sizeof(int), compare_ints);
    return sorted;
}

int tuples_equal(const Tuple *a, const Tuple *b) {
    if (a == NULL || b == NULL) {
        return 0;
    }
    if (a->size != b->size) {
        return 0;
    }
    if (a->size == 0) {
        return 1;
    }
    
    int *sorted_a = copy_sorted_tuple(a);
    int *sorted_b = copy_sorted_tuple(b);
    
    if (sorted_a == NULL || sorted_b == NULL) {
        free(sorted_a);
        free(sorted_b);
        return 0;
    }
    
    size_t cmp_size = (size_t)a->size * sizeof(int);
    int result = memcmp(sorted_a, sorted_b, cmp_size) == 0;
    
    free(sorted_a);
    free(sorted_b);
    return result;
}

int tuple_exists(TupleList *result, const Tuple *tuple) {
    if (result == NULL || tuple == NULL) {
        return 0;
    }
    for (int i = 0; i < result->count; i++) {
        if (tuples_equal(&result->tuples[i], tuple)) {
            return 1;
        }
    }
    return 0;
}

TupleList tuple_intersection(TupleList *list) {
    TupleList result;
    result.tuples = NULL;
    result.count = 0;
    
    if (list == NULL || list->count <= 0) {
        return result;
    }
    
    size_t alloc_size = (size_t)list->count * sizeof(Tuple);
    if (alloc_size / sizeof(Tuple) != (size_t)list->count) {
        return result;
    }
    
    result.tuples = (Tuple *)malloc(alloc_size);
    if (result.tuples == NULL) {
        return result;
    }
    
    for (int i = 0; i < list->count; i++) {
        int is_duplicate = 0;
        for (int j = 0; j < i; j++) {
            if (tuples_equal(&list->tuples[i], &list->tuples[j])) {
                is_duplicate = 1;
                break;
            }
        }
        
        if (!is_duplicate) {
            int count = 0;
            for (int j = 0; j < list->count; j++) {
                if (tuples_equal(&list->tuples[i], &list->tuples[j])) {
                    count++;
                }
            }
            
            if (count > 1 && !tuple_exists(&result, &list->tuples[i])) {
                size_t elem_alloc = (size_t)list->tuples[i].size * sizeof(int);
                if (elem_alloc / sizeof(int) != (size_t)list->tuples[i].size) {
                    for (int k = 0; k < result.count; k++) {
                        free(result.tuples[k].elements);
                    }
                    free(result.tuples);
                    result.tuples = NULL;
                    result.count = 0;
                    return result;
                }
                
                result.tuples[result.count].elements = (int *)malloc(elem_alloc);
                if (result.tuples[result.count].elements == NULL) {
                    for (int k = 0; k < result.count; k++) {
                        free(result.tuples[k].elements);
                    }
                    free(result.tuples);
                    result.tuples = NULL;
                    result.count = 0;
                    return result;
                }
                
                if (list->tuples[i].size > 0) {
                    /* Possible weaknesses found:
                     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                     */
                    memcpy(result.tuples[result.count].elements, list->tuples[i].elements, elem_alloc);
                }
                
                result.tuples[result.count].size = list->tuples[i].size;
                result.count++;
            }
        }
    }
    
    if (result.count == 0) {
        free(result.tuples);
        result.tuples = NULL;
    }
    
    return result;
}

void free_tuple_list(TupleList *list) {
    if (list == NULL || list->tuples == NULL) {
        return;
    }
    for (int i = 0; i < list->count; i++) {
        free(list->tuples[i].elements);
    }
    free(list->tuples);
    list->tuples = NULL;
    list->count = 0;
}

void print_tuple_list(TupleList *list) {
    if (list == NULL || list->tuples == NULL || list->count == 0) {
        printf("[]\n");
        return;
    }
    printf("[");
    for (int i = 0; i < list->count; i++) {
        printf("(");
        for (int j = 0; j < list->tuples[i].size; j++) {
            printf("%d", list->tuples[i].elements[j]);
            if (j < list->tuples[i].size - 1) {
                printf(", ");
            }
        }
        printf(")");
        if (i < list->count - 1) {
            printf(", ");
        }
    }
    printf("]\n");
}

int main(void) {
    int elements1[] = {1, 2, 3};
    int elements2[] = {3, 2, 1};
    int elements3[] = {4, 5, 6};
    int elements4[] = {1, 2, 3};
    int elements5[] = {7, 8};
    int elements6[] = {8, 7};
    
    Tuple tuples[6];
    tuples[0].elements = elements1;
    tuples[0].size = 3;
    tuples[1].elements = elements2;
    tuples[1].size = 3;
    tuples[2].elements = elements3;
    tuples[2].size = 3;
    tuples[3].elements = elements4;
    tuples[3].size = 3;
    tuples[4].elements = elements5;
    tuples[4].size = 2;
    tuples[5].elements = elements6;
    tuples[5].size = 2;
    
    TupleList list;
    list.tuples = tuples;
    list.count = 6;
    
    TupleList result = tuple_intersection(&list);
    
    printf("Intersection: ");
    print_tuple_list(&result);
    
    free_tuple_list(&result);
    
    return 0;
}