#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct {
    int *elems;
    size_t len;
} Tuple;

typedef struct {
    Tuple *tuples;
    size_t count;
} TupleArray;

void join_tuples(TupleArray *arr) {
    for (size_t i = 0; i < arr->count; i++) {
        if (arr->tuples[i].len == 0) continue;
        for (size_t j = i + 1; j < arr->count; j++) {
            if (arr->tuples[j].len == 0) continue;
            if (arr->tuples[i].elems[0] == arr->tuples[j].elems[0]) {
                if (arr->tuples[i].len - 1 > SIZE_MAX - arr->tuples[j].len) {
                    return;
                }
                size_t new_len = arr->tuples[i].len + arr->tuples[j].len - 1;
                if (new_len > SIZE_MAX / sizeof(int)) {
                    return;
                }
                int *new_elems = realloc(arr->tuples[i].elems, new_len * sizeof(int));
                if (!new_elems) {
                    return;
                }
                arr->tuples[i].elems = new_elems;
                size_t copy_len = arr->tuples[j].len - 1;
                size_t copy_size = copy_len * sizeof(int);
                size_t dest_capacity = (new_len - arr->tuples[i].len) * sizeof(int);
                if (dest_capacity < copy_size) {
                    return;
                }
                memcpy(arr->tuples[i].elems + arr->tuples[i].len, arr->tuples[j].elems + 1, copy_size);
                arr->tuples[i].len = new_len;
                
                free(arr->tuples[j].elems);
                arr->tuples[j].elems = NULL;
                arr->tuples[j].len = 0;
            }
        }
    }
    
    size_t write_idx = 0;
    for (size_t i = 0; i < arr->count; i++) {
        if (arr->tuples[i].len > 0) {
            arr->tuples[write_idx++] = arr->tuples[i];
        }
    }
    arr->count = write_idx;
}

void free_tuple_array(TupleArray arr) {
    for (size_t i = 0; i < arr.count; i++) {
        free(arr.tuples[i].elems);
    }
    free(arr.tuples);
}

int main(void) {
    TupleArray arr;
    arr.count = 4;
    arr.tuples = malloc(arr.count * sizeof(Tuple));
    if (!arr.tuples) return EXIT_FAILURE;

    for (size_t i = 0; i < arr.count; i++) {
        arr.tuples[i].elems = NULL;
        arr.tuples[i].len = 0;
    }

    int a0[] = {1, 2, 3};
    int a1[] = {1, 4, 5};
    int a2[] = {2, 6};
    int a3[] = {1, 7};
    int *data[] = {a0, a1, a2, a3};
    size_t lens[] = {3, 3, 2, 2};

    for (size_t i = 0; i < arr.count; i++) {
        arr.tuples[i].len = lens[i];
        if (arr.tuples[i].len > SIZE_MAX / sizeof(int)) {
            free_tuple_array(arr);
            return EXIT_FAILURE;
        }
        arr.tuples[i].elems = malloc(arr.tuples[i].len * sizeof(int));
        if (!arr.tuples[i].elems) {
            free_tuple_array(arr);
            return EXIT_FAILURE;
        }
        size_t dest_size = arr.tuples[i].len * sizeof(int);
        size_t src_size = lens[i] * sizeof(int);
        if (dest_size < src_size) {
            free_tuple_array(arr);
            return EXIT_FAILURE;
        }
        memcpy(arr.tuples[i].elems, data[i], src_size);
    }

    join_tuples(&arr);

    for (size_t i = 0; i < arr.count; i++) {
        for (size_t j = 0; j < arr.tuples[i].len; j++) {
            printf("%d ", arr.tuples[i].elems[j]);
        }
        printf("\n");
    }

    free_tuple_array(arr);

    return EXIT_SUCCESS;
}