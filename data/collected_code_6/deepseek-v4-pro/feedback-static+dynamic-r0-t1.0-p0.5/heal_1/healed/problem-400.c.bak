#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

int compare_tuples(const int *a, const int *b, int size) {
    int *sorted_a = (int *)malloc(size * sizeof(int));
    int *sorted_b = (int *)malloc(size * sizeof(int));
    int result = 0;
    
    if (!sorted_a || !sorted_b) {
        free(sorted_a);
        free(sorted_b);
        return -1;
    }
    
    memcpy(sorted_a, a, size * sizeof(int));
    memcpy(sorted_b, b, size * sizeof(int));
    
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (sorted_a[j] > sorted_a[j + 1]) {
                int temp = sorted_a[j];
                sorted_a[j] = sorted_a[j + 1];
                sorted_a[j + 1] = temp;
            }
            if (sorted_b[j] > sorted_b[j + 1]) {
                int temp = sorted_b[j];
                sorted_b[j] = sorted_b[j + 1];
                sorted_b[j + 1] = temp;
            }
        }
    }
    
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
    list->tuples = NULL;
    list->count = 0;
    list->capacity = 0;
}

int add_tuple_frequency(TupleFrequencyList *list, int *tuple, int size) {
    for (int i = 0; i < list->count; i++) {
        if (list->tuples[i].size == size && 
            compare_tuples(list->tuples[i].elements, tuple, size) == 0) {
            list->tuples[i].frequency++;
            return 0;
        }
    }
    
    if (list->count == list->capacity) {
        int new_capacity = list->capacity == 0 ? 8 : list->capacity * 2;
        TupleFreq *new_tuples = (TupleFreq *)realloc(list->tuples, 
                                                      new_capacity * sizeof(TupleFreq));
        if (!new_tuples) {
            return -1;
        }
        list->tuples = new_tuples;
        list->capacity = new_capacity;
    }
    
    list->tuples[list->count].elements = (int *)malloc(size * sizeof(int));
    if (!list->tuples[list->count].elements) {
        return -1;
    }
    
    memcpy(list->tuples[list->count].elements, tuple, size * sizeof(int));
    list->tuples[list->count].size = size;
    list->tuples[list->count].frequency = 1;
    list->count++;
    
    return 0;
}

void free_tuple_freq_list(TupleFrequencyList *list) {
    for (int i = 0; i < list->count; i++) {
        free(list->tuples[i].elements);
    }
    free(list->tuples);
    list->tuples = NULL;
    list->count = 0;
    list->capacity = 0;
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

void print_tuple_frequencies(TupleFrequencyList *list) {
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

int main() {
    int tuple1[] = {1, 2, 3};
    int tuple2[] = {3, 2, 1};
    int tuple3[] = {4, 5, 6};
    int tuple4[] = {1, 2, 3};
    int tuple5[] = {6, 5, 4};
    int tuple6[] = {7, 8, 9};
    
    int *tuples[] = {tuple1, tuple2, tuple3, tuple4, tuple5, tuple6};
    int tuple_sizes[] = {3, 3, 3, 3, 3, 3};
    int num_tuples = 6;
    
    TupleFrequencyList result;
    
    extract_tuple_frequencies(tuples, tuple_sizes, num_tuples, &result);
    print_tuple_frequencies(&result);
    free_tuple_freq_list(&result);
    
    return 0;
}