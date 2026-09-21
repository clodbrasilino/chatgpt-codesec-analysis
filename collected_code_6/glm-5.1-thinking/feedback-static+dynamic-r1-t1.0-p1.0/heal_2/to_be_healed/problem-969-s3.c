#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
                size_t new_len = arr.tuples[i].len + arr.tuples[j].len - 1;
                int *new_elems = realloc(arr.tuples[i].elems, new_len * sizeof(int));
                if (!new_elems) {
                    return arr;
                }
                arr.tuples[i].elems = new_elems;
                size_t copy_size = (arr.tuples[j].len - 1) * sizeof(int);
                size_t dest_avail = (new_len - arr.tuples[i].len) * sizeof(int);
                if (dest_avail >= copy_size) {
                    /* Possible weaknesses found:
                     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                     */
                    memcpy(arr.tuples[i].elems + arr.tuples[i].len, arr.tuples[j].elems + 1, copy_size);
                }
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

    int a1[] = {1, 2, 3};
    int a2[] = {1, 4, 5};
    int a3[] = {2, 6};
    int a4[] = {1, 7};

    size_t a1_size = sizeof(a1);
    /* Possible weaknesses found:
     *  dest_cap0 is assigned 'a1_size' here.
     */
    size_t dest_cap0 = a1_size;
    /* Possible weaknesses found:
     *  src_size0 is assigned 'a1_size' here.
     */
    size_t src_size0 = a1_size;
    arr.tuples[0].len = a1_size / sizeof(int);
    arr.tuples[0].elems = malloc(dest_cap0);
    /* Possible weaknesses found:
     *  Assuming condition is false
     */
    if (!arr.tuples[0].elems) { free_tuple_array(arr); return EXIT_FAILURE; }
    /* Possible weaknesses found:
     *  Condition 'dest_cap0>=src_size0' is always true
     *  Condition 'dest_cap0>=src_size0' is always true [knownConditionTrueFalse]
     */
    if (dest_cap0 >= src_size0) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(arr.tuples[0].elems, a1, src_size0);
    }

    size_t a2_size = sizeof(a2);
    /* Possible weaknesses found:
     *  dest_cap1 is assigned 'a2_size' here.
     */
    size_t dest_cap1 = a2_size;
    /* Possible weaknesses found:
     *  src_size1 is assigned 'a2_size' here.
     */
    size_t src_size1 = a2_size;
    arr.tuples[1].len = a2_size / sizeof(int);
    arr.tuples[1].elems = malloc(dest_cap1);
    /* Possible weaknesses found:
     *  Assuming condition is false
     */
    if (!arr.tuples[1].elems) { free_tuple_array(arr); return EXIT_FAILURE; }
    /* Possible weaknesses found:
     *  Condition 'dest_cap1>=src_size1' is always true
     *  Condition 'dest_cap1>=src_size1' is always true [knownConditionTrueFalse]
     */
    if (dest_cap1 >= src_size1) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(arr.tuples[1].elems, a2, src_size1);
    }

    size_t a3_size = sizeof(a3);
    /* Possible weaknesses found:
     *  dest_cap2 is assigned 'a3_size' here.
     */
    size_t dest_cap2 = a3_size;
    /* Possible weaknesses found:
     *  src_size2 is assigned 'a3_size' here.
     */
    size_t src_size2 = a3_size;
    arr.tuples[2].len = a3_size / sizeof(int);
    arr.tuples[2].elems = malloc(dest_cap2);
    /* Possible weaknesses found:
     *  Assuming condition is false
     */
    if (!arr.tuples[2].elems) { free_tuple_array(arr); return EXIT_FAILURE; }
    /* Possible weaknesses found:
     *  Condition 'dest_cap2>=src_size2' is always true
     *  Condition 'dest_cap2>=src_size2' is always true [knownConditionTrueFalse]
     */
    if (dest_cap2 >= src_size2) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(arr.tuples[2].elems, a3, src_size2);
    }

    size_t a4_size = sizeof(a4);
    /* Possible weaknesses found:
     *  dest_cap3 is assigned 'a4_size' here.
     */
    size_t dest_cap3 = a4_size;
    /* Possible weaknesses found:
     *  src_size3 is assigned 'a4_size' here.
     */
    size_t src_size3 = a4_size;
    arr.tuples[3].len = a4_size / sizeof(int);
    arr.tuples[3].elems = malloc(dest_cap3);
    /* Possible weaknesses found:
     *  Assuming condition is false
     */
    if (!arr.tuples[3].elems) { free_tuple_array(arr); return EXIT_FAILURE; }
    /* Possible weaknesses found:
     *  Condition 'dest_cap3>=src_size3' is always true
     *  Condition 'dest_cap3>=src_size3' is always true [knownConditionTrueFalse]
     */
    if (dest_cap3 >= src_size3) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(arr.tuples[3].elems, a4, src_size3);
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