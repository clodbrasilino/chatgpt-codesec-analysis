#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct {
    int *elements;
    int size;
    int frequency;
} TupleFreq;

typedef struct {
    TupleFreq *tuples;
    int count;
    int capacity;
} TupleFrequencyList;

static int int_cmp(const void *a, const void *b) {
    int ia = *(const int *)a;
    int ib = *(const int *)b;
    return (ia > ib) - (ia < ib);
}

int compare_tuples(const int *a, const int *b, int size) {
    int *sorted_a = NULL;
    int *sorted_b = NULL;
    int result = 0;
    size_t mem_size;
    
    if (size <= 0) {
        return -1;
    }
    
    if ((size_t)size > SIZE_MAX / sizeof(int)) {
        return -1;
    }
    
    mem_size = (size_t)size * sizeof(int);
    
    sorted_a = (int *)malloc(mem_size);
    sorted_b = (int *)malloc(mem_size);
    
    if (!sorted_a || !sorted_b) {
        free(sorted_a);
        free(sorted_b);
        return -1;
    }
    
    if (mem_size > 0) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(sorted_a, a, mem_size);
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(sorted_b, b, mem_size);
    }
    
    qsort(sorted_a, (size_t)size, sizeof(int), int_cmp);
    qsort(sorted_b, (size_t)size, sizeof(int), int_cmp);
    
    for (int i = 0; i < size; i++) {
        if (sorted_a[i] != sorted_b[i]) {
            result = sorted_a[i] - sorted_b[i];
            break;
        }
    }
    
    free(sorted_a);
    free(sorted_b);
    return result;
}

void init_tuple_freq_list(TupleFrequencyList *list) {
    if (list) {
        list->tuples = NULL;
        list->count = 0;
        list->capacity = 0;
    }
}

static int validate_allocation(size_t nelem, size_t size) {
    return (nelem > 0 && size > 0 && nelem <= SIZE_MAX / size) ? 1 : 0;
}

int add_tuple_frequency(TupleFrequencyList *list, const int *tuple, int size) {
    size_t mem_size;
    
    if (!list || !tuple || size <= 0) {
        return -1;
    }
    
    if ((size_t)size > SIZE_MAX / sizeof(int)) {
        return -1;
    }
    
    mem_size = (size_t)size * sizeof(int);
    
    for (int i = 0; i < list->count; i++) {
        if (list->tuples[i].size == size && 
            compare_tuples(list->tuples[i].elements, tuple, size) == 0) {
            list->tuples[i].frequency++;
            return 0;
        }
    }
    
    if (list->count == list->capacity) {
        int new_capacity = list->capacity == 0 ? 8 : list->capacity * 2;
        if (new_capacity <= 0 || !validate_allocation((size_t)new_capacity, sizeof(TupleFreq))) {
            return -1;
        }
        TupleFreq *new_tuples = (TupleFreq *)realloc(list->tuples, 
                                                      (size_t)new_capacity * sizeof(TupleFreq));
        if (!new_tuples) {
            return -1;
        }
        list->tuples = new_tuples;
        list->capacity = new_capacity;
    }
    
    list->tuples[list->count].elements = (int *)malloc(mem_size);
    if (!list->tuples[list->count].elements) {
        return -1;
    }
    
    if (mem_size > 0) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(list->tuples[list->count].elements, tuple, mem_size);
    }
    list->tuples[list->count].size = size;
    list->tuples[list->count].frequency = 1;
    list->count++;
    
    return 0;
}

void free_tuple_freq_list(TupleFrequencyList *list) {
    if (list) {
        for (int i = 0; i < list->count; i++) {
            free(list->tuples[i].elements);
            list->tuples[i].elements = NULL;
        }
        free(list->tuples);
        list->tuples = NULL;
        list->count = 0;
        list->capacity = 0;
    }
}

void extract_tuple_frequencies(int **tuples, const int *tuple_sizes, int num_tuples, 
                               TupleFrequencyList *result) {
    init_tuple_freq_list(result);
    
    for (int i = 0; i < num_tuples; i++) {
        if (add_tuple_frequency(result, tuples[i], tuple_sizes[i]) != 0) {
            free_tuple_freq_list(result);
            init_tuple_freq_list(result);
            return;
        }
    }
}

void print_tuple_frequencies(const TupleFrequencyList *list) {
    if (!list) return;
    for (int i = 0; i < list->count; i++) {
        printf("Tuple (");
        for (int j = 0; j < list->tuples[i].size; j++) {
            printf("%d", list->tuples[i].elements[j]);
            if (j < list->tuples[i].size - 1) {
                printf(", ");
            }
        }
        printf("): %d\n", list->tuples[i].frequency);
    }
}

int main(void) {
    int tuple1[] = {1, 2, 3};
    int tuple2[] = {3, 2, 1};
    int tuple3[] = {4, 5, 6};
    int tuple4[] = {1, 2, 3};
    int tuple5[] = {6, 5, 4};
    int tuple6[] = {7, 8, 9};
    
    int *tuples[] = {tuple1, tuple2, tuple3, tuple4, tuple5, tuple6};
    const int tuple_sizes[] = {3, 3, 3, 3, 3, 3};
    int num_tuples = 6;
    
    TupleFrequencyList result;
    
    extract_tuple_frequencies(tuples, tuple_sizes, num_tuples, &result);
    print_tuple_frequencies(&result);
    free_tuple_freq_list(&result);
    
    return 0;
}