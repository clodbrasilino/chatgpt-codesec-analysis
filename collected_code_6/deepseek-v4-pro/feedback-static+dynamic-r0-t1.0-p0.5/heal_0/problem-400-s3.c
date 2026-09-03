#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int *elements;
    int size;
    int frequency;
} TupleFreq;

int compare_tuples(const int *a, const int *b, int size) {
    int *sorted_a = (int *)malloc(size * sizeof(int));
    int *sorted_b = (int *)malloc(size * sizeof(int));
    int i, j, temp;
    
    if (!sorted_a || !sorted_b) {
        free(sorted_a);
        free(sorted_b);
        return -1;
    }
    
    memcpy(sorted_a, a, size * sizeof(int));
    memcpy(sorted_b, b, size * sizeof(int));
    
    for (i = 0; i < size - 1; i++) {
        for (j = 0; j < size - i - 1; j++) {
            if (sorted_a[j] > sorted_a[j + 1]) {
                temp = sorted_a[j];
                sorted_a[j] = sorted_a[j + 1];
                sorted_a[j + 1] = temp;
            }
            if (sorted_b[j] > sorted_b[j + 1]) {
                temp = sorted_b[j];
                sorted_b[j] = sorted_b[j + 1];
                sorted_b[j + 1] = temp;
            }
        }
    }
    
    for (i = 0; i < size; i++) {
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
    int *processed = NULL;
    int i, j, found;
    
    if (!tuples || tuple_count <= 0 || tuple_size <= 0 || !result_count) {
        *result_count = 0;
        return NULL;
    }
    
    frequencies = (TupleFreq *)malloc(tuple_count * sizeof(TupleFreq));
    processed = (int *)calloc(tuple_count, sizeof(int));
    
    if (!frequencies || !processed) {
        free(frequencies);
        free(processed);
        *result_count = 0;
        return NULL;
    }
    
    *result_count = 0;
    
    for (i = 0; i < tuple_count; i++) {
        if (processed[i]) {
            continue;
        }
        
        frequencies[*result_count].elements = (int *)malloc(tuple_size * sizeof(int));
        if (!frequencies[*result_count].elements) {
            for (j = 0; j < *result_count; j++) {
                free(frequencies[j].elements);
            }
            free(frequencies);
            free(processed);
            *result_count = 0;
            return NULL;
        }
        
        memcpy(frequencies[*result_count].elements, tuples[i], tuple_size * sizeof(int));
        frequencies[*result_count].size = tuple_size;
        frequencies[*result_count].frequency = 1;
        processed[i] = 1;
        
        for (j = i + 1; j < tuple_count; j++) {
            if (!processed[j] && compare_tuples(tuples[i], tuples[j], tuple_size) == 1) {
                frequencies[*result_count].frequency++;
                processed[j] = 1;
            }
        }
        
        (*result_count)++;
    }
    
    free(processed);
    return frequencies;
}

int main(void) {
    int tuple_size = 3;
    int tuple_count = 6;
    int **tuples = (int **)malloc(tuple_count * sizeof(int *));
    int i, j;
    TupleFreq *result;
    int result_count;
    
    for (i = 0; i < tuple_count; i++) {
        tuples[i] = (int *)malloc(tuple_size * sizeof(int));
    }
    
    tuples[0][0] = 1; tuples[0][1] = 2; tuples[0][2] = 3;
    tuples[1][0] = 3; tuples[1][1] = 2; tuples[1][2] = 1;
    tuples[2][0] = 4; tuples[2][1] = 5; tuples[2][2] = 6;
    tuples[3][0] = 1; tuples[3][1] = 2; tuples[3][2] = 3;
    tuples[4][0] = 7; tuples[4][1] = 8; tuples[4][2] = 9;
    tuples[5][0] = 6; tuples[5][1] = 4; tuples[5][2] = 5;
    
    result = extract_tuple_frequencies(tuples, tuple_count, tuple_size, &result_count);
    
    if (result) {
        for (i = 0; i < result_count; i++) {
            printf("Tuple (");
            for (j = 0; j < result[i].size; j++) {
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
    
    for (i = 0; i < tuple_count; i++) {
        free(tuples[i]);
    }
    free(tuples);
    
    return 0;
}