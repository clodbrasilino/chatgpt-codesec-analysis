#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    size_t size;
} Tuple;

typedef struct {
    int first;
    int second;
} Pair;

typedef struct {
    Pair *data;
    size_t size;
} ZippedTuple;

Tuple* create_tuple(const int *arr, size_t size) {
    if (arr == NULL || size == 0) {
        return NULL;
    }
    
    Tuple *tuple = (Tuple*)malloc(sizeof(Tuple));
    if (tuple == NULL) {
        return NULL;
    }
    
    tuple->data = (int*)malloc(size * sizeof(int));
    if (tuple->data == NULL) {
        free(tuple);
        return NULL;
    }
    
    for (size_t i = 0; i < size; i++) {
        tuple->data[i] = arr[i];
    }
    
    tuple->size = size;
    return tuple;
}

ZippedTuple* zip_tuples(const Tuple *t1, const Tuple *t2) {
    if (t1 == NULL || t2 == NULL || t1->data == NULL || t2->data == NULL) {
        return NULL;
    }
    
    size_t min_size = (t1->size < t2->size) ? t1->size : t2->size;
    
    ZippedTuple *zipped = (ZippedTuple*)malloc(sizeof(ZippedTuple));
    if (zipped == NULL) {
        return NULL;
    }
    
    zipped->data = (Pair*)malloc(min_size * sizeof(Pair));
    if (zipped->data == NULL) {
        free(zipped);
        return NULL;
    }
    
    for (size_t i = 0; i < min_size; i++) {
        zipped->data[i].first = t1->data[i];
        zipped->data[i].second = t2->data[i];
    }
    
    zipped->size = min_size;
    return zipped;
}

void free_tuple(Tuple *tuple) {
    if (tuple != NULL) {
        free(tuple->data);
        free(tuple);
    }
}

void free_zipped(ZippedTuple *zipped) {
    if (zipped != NULL) {
        free(zipped->data);
        free(zipped);
    }
}

void print_zipped(const ZippedTuple *zipped) {
    if (zipped == NULL || zipped->data == NULL) {
        return;
    }
    
    printf("[");
    for (size_t i = 0; i < zipped->size; i++) {
        printf("(%d, %d)", zipped->data[i].first, zipped->data[i].second);
        if (i < zipped->size - 1) {
            printf(", ");
        }
    }
    printf("]\n");
}

int main(void) {
    int arr1[] = {1, 2, 3, 4};
    int arr2[] = {5, 6, 7, 8};
    size_t size1 = sizeof(arr1) / sizeof(arr1[0]);
    size_t size2 = sizeof(arr2) / sizeof(arr2[0]);
    
    Tuple *tuple1 = create_tuple(arr1, size1);
    if (tuple1 == NULL) {
        fprintf(stderr, "Failed to create tuple1\n");
        return EXIT_FAILURE;
    }
    
    Tuple *tuple2 = create_tuple(arr2, size2);
    if (tuple2 == NULL) {
        fprintf(stderr, "Failed to create tuple2\n");
        free_tuple(tuple1);
        return EXIT_FAILURE;
    }
    
    ZippedTuple *zipped = zip_tuples(tuple1, tuple2);
    if (zipped == NULL) {
        fprintf(stderr, "Failed to zip tuples\n");
        free_tuple(tuple1);
        free_tuple(tuple2);
        return EXIT_FAILURE;
    }
    
    print_zipped(zipped);
    
    free_zipped(zipped);
    free_tuple(tuple1);
    free_tuple(tuple2);
    
    return EXIT_SUCCESS;
}