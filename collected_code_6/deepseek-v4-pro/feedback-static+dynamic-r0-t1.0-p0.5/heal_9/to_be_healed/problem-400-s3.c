#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <limits.h>

typedef struct {
    int *elements;
    int size;
    int frequency;
} TupleFreq;

static int compare_int(const void *a, const void *b) {
    int diff = *(const int *)a - *(const int *)b;
    return (diff > 0) - (diff < 0);
}

static int compare_tuples(const int *a, const int *b, int size) {
    int *sorted_a = NULL;
    int *sorted_b = NULL;
    size_t alloc_size;
    
    if (!a || !b || size <= 0) {
        return 0;
    }
    
    if (size > (int)(SIZE_MAX / sizeof(int))) {
        return -1;
    }
    
    alloc_size = (size_t)size * sizeof(int);
    if (alloc_size == 0) {
        return -1;
    }
    
    sorted_a = (int *)malloc(alloc_size);
    sorted_b = (int *)malloc(alloc_size);
    
    if (!sorted_a || !sorted_b) {
        free(sorted_a);
        free(sorted_b);
        return -1;
    }
    
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(sorted_a, a, alloc_size);
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(sorted_b, b, alloc_size);
    
    qsort(sorted_a, (size_t)size, sizeof(int), compare_int);
    qsort(sorted_b, (size_t)size, sizeof(int), compare_int);
    
    for (int i = 0; i < size; i++) {
        if (sorted_a[i] != sorted_b[i]) {
            free(sorted_a);
            free(sorted_b);
            return 0;
        }
    }
    
    free(sorted_a);
    free(sorted_b);
    return 1;
}

TupleFreq *extract_tuple_frequencies(int **tuples, int tuple_count, int tuple_size, int *result_count) {
    TupleFreq *frequencies = NULL;
    int *boolean_processed = NULL;
    size_t alloc_size;
    
    if (!tuples || tuple_count <= 0 || tuple_size <= 0 || !result_count) {
        if (result_count) {
            *result_count = 0;
        }
        return NULL;
    }
    
    if ((size_t)tuple_count > SIZE_MAX / sizeof(TupleFreq) ||
        (size_t)tuple_size > SIZE_MAX / sizeof(int)) {
        *result_count = 0;
        return NULL;
    }
    
    frequencies = (TupleFreq *)calloc((size_t)tuple_count, sizeof(TupleFreq));
    boolean_processed = (int *)calloc((size_t)tuple_count, sizeof(int));
    
    if (!frequencies || !boolean_processed) {
        free(frequencies);
        free(boolean_processed);
        *result_count = 0;
        return NULL;
    }
    
    *result_count = 0;
    alloc_size = (size_t)tuple_size * sizeof(int);
    
    for (int i = 0; i < tuple_count; i++) {
        if (boolean_processed[i]) {
            continue;
        }
        
        if (!tuples[i]) {
            for (int j = 0; j < *result_count; j++) {
                free(frequencies[j].elements);
            }
            free(frequencies);
            free(boolean_processed);
            *result_count = 0;
            return NULL;
        }
        
        frequencies[*result_count].elements = (int *)malloc(alloc_size);
        if (!frequencies[*result_count].elements) {
            for (int j = 0; j < *result_count; j++) {
                free(frequencies[j].elements);
            }
            free(frequencies);
            free(boolean_processed);
            *result_count = 0;
            return NULL;
        }
        
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(frequencies[*result_count].elements, tuples[i], alloc_size);
        frequencies[*result_count].size = tuple_size;
        frequencies[*result_count].frequency = 1;
        boolean_processed[i] = 1;
        
        for (int j = i + 1; j < tuple_count; j++) {
            if (!boolean_processed[j] && compare_tuples(tuples[i], tuples[j], tuple_size) == 1) {
                frequencies[*result_count].frequency++;
                boolean_processed[j] = 1;
            }
        }
        
        (*result_count)++;
    }
    
    free(boolean_processed);
    return frequencies;
}

int main(void) {
    int tuple_size = 3;
    int tuple_count = 6;
    int **tuples;
    TupleFreq *result;
    int result_count;
    
    tuples = (int **)malloc((size_t)tuple_count * sizeof(int *));
    if (!tuples) {
        return 1;
    }
    
    for (int i = 0; i < tuple_count; i++) {
        tuples[i] = (int *)malloc((size_t)tuple_size * sizeof(int));
        if (!tuples[i]) {
            for (int j = 0; j < i; j++) {
                free(tuples[j]);
            }
            free(tuples);
            return 1;
        }
    }
    
    tuples[0][0] = 1; tuples[0][1] = 2; tuples[0][2] = 3;
    tuples[1][0] = 3; tuples[1][1] = 2; tuples[1][2] = 1;
    tuples[2][0] = 4; tuples[2][1] = 5; tuples[2][2] = 6;
    tuples[3][0] = 1; tuples[3][1] = 2; tuples[3][2] = 3;
    tuples[4][0] = 7; tuples[4][1] = 8; tuples[4][2] = 9;
    tuples[5][0] = 6; tuples[5][1] = 4; tuples[5][2] = 5;
    
    result = extract_tuple_frequencies(tuples, tuple_count, tuple_size, &result_count);
    
    if (result) {
        for (int i = 0; i < result_count; i++) {
            printf("Tuple (");
            for (int j = 0; j < result[i].size; j++) {
                printf("%d", result[i].elements[j]);
                if (j < result[i].size - 1) {
                    printf(", ");
                }
            }
            printf(") - Frequency: %d\n", result[i].frequency);
            free(result[i].elements);
        }
        free(result);
    }
    
    for (int i = 0; i < tuple_count; i++) {
        free(tuples[i]);
    }
    free(tuples);
    
    return 0;
}