#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *elements;
    int len;
} Tuple;

Tuple* tuple_create(int *arr, int len) {
    if (arr == NULL || len < 0) {
        return NULL;
    }
    Tuple *t = (Tuple*)malloc(sizeof(Tuple));
    if (t == NULL) {
        return NULL;
    }
    t->elements = (int*)malloc(len * sizeof(int));
    if (t->elements == NULL) {
        free(t);
        return NULL;
    }
    for (int i = 0; i < len; i++) {
        t->elements[i] = arr[i];
    }
    t->len = len;
    return t;
}

void tuple_destroy(Tuple *t) {
    if (t != NULL) {
        free(t->elements);
        free(t);
    }
}

int check_tuple_k_elements(Tuple *t, int k) {
    if (t == NULL || k < 0) {
        return 0;
    }
    return t->len == k;
}

int main() {
    int arr1[] = {1, 2, 3};
    int arr2[] = {4, 5};
    
    Tuple *t1 = tuple_create(arr1, 3);
    Tuple *t2 = tuple_create(arr2, 2);
    
    if (t1 == NULL || t2 == NULL) {
        fprintf(stderr, "Allocation failed\n");
        if (t1) tuple_destroy(t1);
        if (t2) tuple_destroy(t2);
        return 1;
    }
    
    int k1 = 3;
    int result1 = check_tuple_k_elements(t1, k1);
    printf("%d\n", result1);
    
    int k2 = 3;
    int result2 = check_tuple_k_elements(t2, k2);
    printf("%d\n", result2);
    
    tuple_destroy(t1);
    tuple_destroy(t2);
    
    return 0;
}