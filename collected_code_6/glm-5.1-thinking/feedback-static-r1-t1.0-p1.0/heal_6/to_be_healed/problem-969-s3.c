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

TupleArray join_tuples(TupleArray arr) {
    for (size_t i = 0; i < arr.count; i++) {
        if (arr.tuples[i].len == 0) continue;
        for (size_t j = i + 1; j < arr.count; j++) {
            if (arr.tuples[j].len == 0) continue;
            if (arr.tuples[i].elems[0] == arr.tuples[j].elems[0]) {
                if (arr.tuples[i].len - 1 > SIZE_MAX - arr.tuples[j].len) {
                    return arr;
                }
                size_t new_len = arr.tuples[i].len + arr.tuples[j].len - 1;
                if (new_len > SIZE_MAX / sizeof(int)) {
                    return arr;
                }
                int *new_elems = realloc(arr.tuples[i].elems, new_len * sizeof(int));
                if (!new_elems) {
                    return arr;
                }
                arr.tuples[i].elems = new_elems;
                size_t copy_len = arr.tuples[j].len - 1;
                size_t copy_size = copy_len * sizeof(int);
                size_t dest_capacity = (new_len - arr.tuples[i].len) * sizeof(int);
                if (dest_capacity < copy_size) {
                    return arr;
                }
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(arr.tuples[i].elems + arr.tuples[i].len, arr.tuples[j].elems + 1, copy_size);
                arr.tuples[i].len = new_len;
                
                free(arr.tuples[j].elems);
                arr.tuples[j].elems = NULL;
                arr.tuples[j].len = 0;
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
    }

    {
        int a[] = {1, 2, 3};
        arr.tuples[0].len = sizeof(a) / sizeof(a[0]);
        if (arr.tuples[0].len > SIZE_MAX / sizeof(int)) { free_tuple_array(arr); return EXIT_FAILURE; }
        arr.tuples[0].elems = malloc(arr.tuples[0].len * sizeof(int));
        if (!arr.tuples[0].elems) { free_tuple_array(arr); return EXIT_FAILURE; }
        size_t dest_size = arr.tuples[0].len * sizeof(int);
        if (dest_size < sizeof(a)) { free_tuple_array(arr); return EXIT_FAILURE; }
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(arr.tuples[0].elems, a, sizeof(a));
    }

    {
        int a[] = {1, 4, 5};
        arr.tuples[1].len = sizeof(a) / sizeof(a[0]);
        if (arr.tuples[1].len > SIZE_MAX / sizeof(int)) { free_tuple_array(arr); return EXIT_FAILURE; }
        arr.tuples[1].elems = malloc(arr.tuples[1].len * sizeof(int));
        if (!arr.tuples[1].elems) { free_tuple_array(arr); return EXIT_FAILURE; }
        size_t dest_size = arr.tuples[1].len * sizeof(int);
        if (dest_size < sizeof(a)) { free_tuple_array(arr); return EXIT_FAILURE; }
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(arr.tuples[1].elems, a, sizeof(a));
    }

    {
        int a[] = {2, 6};
        arr.tuples[2].len = sizeof(a) / sizeof(a[0]);
        if (arr.tuples[2].len > SIZE_MAX / sizeof(int)) { free_tuple_array(arr); return EXIT_FAILURE; }
        arr.tuples[2].elems = malloc(arr.tuples[2].len * sizeof(int));
        if (!arr.tuples[2].elems) { free_tuple_array(arr); return EXIT_FAILURE; }
        size_t dest_size = arr.tuples[2].len * sizeof(int);
        if (dest_size < sizeof(a)) { free_tuple_array(arr); return EXIT_FAILURE; }
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(arr.tuples[2].elems, a, sizeof(a));
    }

    {
        int a[] = {1, 7};
        arr.tuples[3].len = sizeof(a) / sizeof(a[0]);
        if (arr.tuples[3].len > SIZE_MAX / sizeof(int)) { free_tuple_array(arr); return EXIT_FAILURE; }
        arr.tuples[3].elems = malloc(arr.tuples[3].len * sizeof(int));
        if (!arr.tuples[3].elems) { free_tuple_array(arr); return EXIT_FAILURE; }
        size_t dest_size = arr.tuples[3].len * sizeof(int);
        if (dest_size < sizeof(a)) { free_tuple_array(arr); return EXIT_FAILURE; }
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(arr.tuples[3].elems, a, sizeof(a));
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