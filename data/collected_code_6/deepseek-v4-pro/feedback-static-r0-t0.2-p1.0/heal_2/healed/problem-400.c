#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int *elements;
    int size;
    int frequency;
} Tuple;

typedef struct {
    Tuple *tuples;
    int count;
    int capacity;
} TupleList;

static int compare_ints(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

static int compare_tuples(const int *a, const int *b, int size) {
    int *a_sorted = (int *)malloc(size * sizeof(int));
    int *b_sorted = (int *)malloc(size * sizeof(int));
    int result = 0;
    int i;
    
    if (!a_sorted || !b_sorted) {
        free(a_sorted);
        free(b_sorted);
        return -1;
    }
    
    if (size > 0) {
        memcpy(a_sorted, a, (size_t)size * sizeof(int));
        memcpy(b_sorted, b, (size_t)size * sizeof(int));
    }
    
    qsort(a_sorted, size, sizeof(int), compare_ints);
    qsort(b_sorted, size, sizeof(int), compare_ints);
    
    for (i = 0; i < size; i++) {
        if (a_sorted[i] != b_sorted[i]) {
            result = a_sorted[i] - b_sorted[i];
            break;
        }
    }
    
    free(a_sorted);
    free(b_sorted);
    return result;
}

static void add_tuple(TupleList *list, const int *elements, int size) {
    int i;
    
    for (i = 0; i < list->count; i++) {
        if (list->tuples[i].size == size && 
            compare_tuples(list->tuples[i].elements, elements, size) == 0) {
            list->tuples[i].frequency++;
            return;
        }
    }
    
    if (list->count >= list->capacity) {
        size_t new_capacity = list->capacity == 0 ? 16 : (size_t)list->capacity * 2;
        if (new_capacity > SIZE_MAX / sizeof(Tuple)) {
            for (i = 0; i < list->count; i++) {
                free(list->tuples[i].elements);
            }
            free(list->tuples);
            exit(1);
        }
        Tuple *new_tuples = (Tuple *)realloc(list->tuples, new_capacity * sizeof(Tuple));
        if (!new_tuples) {
            for (i = 0; i < list->count; i++) {
                free(list->tuples[i].elements);
            }
            free(list->tuples);
            exit(1);
        }
        list->tuples = new_tuples;
        list->capacity = (int)new_capacity;
    }
    
    list->tuples[list->count].elements = (int *)malloc((size_t)size * sizeof(int));
    if (!list->tuples[list->count].elements) {
        for (i = 0; i < list->count; i++) {
            free(list->tuples[i].elements);
        }
        free(list->tuples);
        exit(1);
    }
    
    if (size > 0) {
        memcpy(list->tuples[list->count].elements, elements, (size_t)size * sizeof(int));
    }
    list->tuples[list->count].size = size;
    list->tuples[list->count].frequency = 1;
    list->count++;
}

void extract_tuple_frequencies(int **tuples, int tuple_count, int tuple_size, 
                                int ***unique_tuples, int **frequencies, int *unique_count) {
    TupleList list = {NULL, 0, 0};
    int i, j;
    
    for (i = 0; i < tuple_count; i++) {
        add_tuple(&list, tuples[i], tuple_size);
    }
    
    *unique_count = list.count;
    *unique_tuples = (int **)malloc((size_t)list.count * sizeof(int *));
    *frequencies = (int *)malloc((size_t)list.count * sizeof(int));
    
    if (!*unique_tuples || !*frequencies) {
        free(*unique_tuples);
        free(*frequencies);
        for (i = 0; i < list.count; i++) {
            free(list.tuples[i].elements);
        }
        free(list.tuples);
        exit(1);
    }
    
    for (i = 0; i < list.count; i++) {
        (*unique_tuples)[i] = (int *)malloc((size_t)tuple_size * sizeof(int));
        if (!(*unique_tuples)[i]) {
            for (j = 0; j < i; j++) {
                free((*unique_tuples)[j]);
            }
            free(*unique_tuples);
            free(*frequencies);
            for (j = 0; j < list.count; j++) {
                free(list.tuples[j].elements);
            }
            free(list.tuples);
            exit(1);
        }
        if (tuple_size > 0) {
            memcpy((*unique_tuples)[i], list.tuples[i].elements, (size_t)tuple_size * sizeof(int));
        }
        (*frequencies)[i] = list.tuples[i].frequency;
    }
    
    for (i = 0; i < list.count; i++) {
        free(list.tuples[i].elements);
    }
    free(list.tuples);
}

int main(void) {
    int tuple1[] = {1, 2, 3};
    int tuple2[] = {3, 2, 1};
    int tuple3[] = {4, 5, 6};
    int tuple4[] = {1, 2, 3};
    int tuple5[] = {6, 5, 4};
    int tuple6[] = {7, 8, 9};
    
    int *tuples[] = {tuple1, tuple2, tuple3, tuple4, tuple5, tuple6};
    int **unique_tuples = NULL;
    int *frequencies = NULL;
    int unique_count = 0;
    int i, j;
    
    extract_tuple_frequencies(tuples, 6, 3, &unique_tuples, &frequencies, &unique_count);
    
    printf("Unique tuples and their frequencies:\n");
    for (i = 0; i < unique_count; i++) {
        printf("(");
        for (j = 0; j < 3; j++) {
            printf("%d", unique_tuples[i][j]);
            if (j < 2) {
                printf(", ");
            }
        }
        printf(") -> %d\n", frequencies[i]);
    }
    
    for (i = 0; i < unique_count; i++) {
        free(unique_tuples[i]);
    }
    free(unique_tuples);
    free(frequencies);
    
    return 0;
}