#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int *elems;
    size_t len;
    size_t capacity;
} Tuple;

typedef struct {
    Tuple *tuples;
    size_t count;
} TupleArray;

TupleArray join_tuples(TupleArray arr) {
    for (size_t i = 0; i < arr.count; i++) {
        if (arr.tuples[i].len == 0) continue;
        for (size_t j = i + 1; j < arr.count; j++) {
            if (arr.tuples[j].len == 0) continue;
            if (arr.tuples[i].elems[0] == arr.tuples[j].elems[0]) {
                size_t new_len = arr.tuples[i].len + arr.tuples[j].len - 1;
                int *new_elems = realloc(arr.tuples[i].elems, new_len * sizeof(int));
                if (!new_elems) {
                    return arr;
                }
                arr.tuples[i].elems = new_elems;
                arr.tuples[i].capacity = new_len;
                
                size_t copy_len = arr.tuples[j].len - 1;
                if (arr.tuples[i].capacity >= arr.tuples[i].len + copy_len) {
                    /* Possible weaknesses found:
                     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                     */
                    memcpy(arr.tuples[i].elems + arr.tuples[i].len, arr.tuples[j].elems + 1, copy_len * sizeof(int));
                }
                arr.tuples[i].len = new_len;
                
                free(arr.tuples[j].elems);
                arr.tuples[j].elems = NULL;
                arr.tuples[j].len = 0;
                arr.tuples[j].capacity = 0;
            }
        }
    }
    
    size_t write_idx = 0;
    for (size_t i = 0; i < arr.count; i++) {
        if (arr.tuples[i].len > 0) {
            arr.tuples[write_idx++] = arr.tuples[i];
        }
    }
    arr.count = write_idx;
    
    return arr;
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
        arr.tuples[i].capacity = 0;
    }

    int a1[] = {1, 2, 3};
    int a2[] = {1, 4, 5};
    int a3[] = {2, 6};
    int a4[] = {1, 7};

    arr.tuples[0].len = sizeof(a1) / sizeof(int);
    arr.tuples[0].capacity = arr.tuples[0].len;
    arr.tuples[0].elems = malloc(arr.tuples[0].capacity * sizeof(int));
    if (!arr.tuples[0].elems) { free_tuple_array(arr); return EXIT_FAILURE; }
    if (arr.tuples[0].len <= arr.tuples[0].capacity) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(arr.tuples[0].elems, a1, arr.tuples[0].len * sizeof(int));
    }

    arr.tuples[1].len = sizeof(a2) / sizeof(int);
    arr.tuples[1].capacity = arr.tuples[1].len;
    arr.tuples[1].elems = malloc(arr.tuples[1].capacity * sizeof(int));
    if (!arr.tuples[1].elems) { free_tuple_array(arr); return EXIT_FAILURE; }
    if (arr.tuples[1].len <= arr.tuples[1].capacity) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(arr.tuples[1].elems, a2, arr.tuples[1].len * sizeof(int));
    }

    arr.tuples[2].len = sizeof(a3) / sizeof(int);
    arr.tuples[2].capacity = arr.tuples[2].len;
    arr.tuples[2].elems = malloc(arr.tuples[2].capacity * sizeof(int));
    if (!arr.tuples[2].elems) { free_tuple_array(arr); return EXIT_FAILURE; }
    if (arr.tuples[2].len <= arr.tuples[2].capacity) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(arr.tuples[2].elems, a3, arr.tuples[2].len * sizeof(int));
    }

    arr.tuples[3].len = sizeof(a4) / sizeof(int);
    arr.tuples[3].capacity = arr.tuples[3].len;
    arr.tuples[3].elems = malloc(arr.tuples[3].capacity * sizeof(int));
    if (!arr.tuples[3].elems) { free_tuple_array(arr); return EXIT_FAILURE; }
    if (arr.tuples[3].len <= arr.tuples[3].capacity) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(arr.tuples[3].elems, a4, arr.tuples[3].len * sizeof(int));
    }

    TupleArray joined = join_tuples(arr);

    for (size_t i = 0; i < joined.count; i++) {
        for (size_t j = 0; j < joined.tuples[i].len; j++) {
            printf("%d ", joined.tuples[i].elems[j]);
        }
        printf("\n");
    }

    free_tuple_array(joined);

    return EXIT_SUCCESS;
}